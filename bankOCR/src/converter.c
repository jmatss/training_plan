#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "converter.h"

static uint64_t pipes_to_hash(char digit[DIGIT_SIZE]);
static uint8_t lookup_digit(uint64_t hash);
static uint64_t lookup_hash(uint8_t digit);
static int lookup_corrections(uint64_t hash, uint8_t *corrections, size_t *size);

/**
 *  _     _  _     _  _  _  _  _ 
 * | |  | _| _||_||_ |_   ||_||_|
 * |_|  ||_  _|  | _||_|  ||_| _|
 * 
 * ("x" represents a whitespace)
 *   0 => x_x |x| |_|
 *   1 => xxx xx| xx|
 *   2 => x_x x_| |_x
 *   3 => x_x x_| x_|
 *   4 => xxx |_| xx|
 *   5 => x_x |_x x_|
 *   6 => x_x |_x |_|
 *   7 => x_x xx| xx|
 *   8 => x_x |_| |_|
 *   9 => x_x |_| x_|
 */

/**
 * Given the string containing the account number in "pipe" format, converts it
 * into a integer number. Returns null if everything worked correctly, returns
 * a string literal otherwise.
 * A digit with a value of "UINT8_MAX" represents a invalid character.
 */
const char *convert(const char *account_number[ROWS], uint8_t result_digits[DIGITS_LEN])
{
    if (NULL == account_number)
    {
        return "Given `account_number` is NULL.";
    }

    // How can one ensure that the amount of ROWS are correct?
    // Ensure all columns in the input are correct length.
    for (size_t i = 0; i < ROWS; i++)
    {
        if (COLS != strlen(account_number[i]))
        {
            return "Incorrect amount of chars in a row.";
        }
    }

    char pipes[DIGITS_LEN][DIGIT_SIZE];

    // "Groups" the pipes that are currently stored in three rows into the pipes
    // belonging to a specific digit.
    // Example (should actually be 9 digits), calling this function with:
    //                                     ROW
    //   _  _                            0  1  2
    //  | ||_|       =>     pipes[0] = " _ | ||_|"  (all pipes in the zero laid out in a row)
    //  |_||_|              pipes[1] = " _ |_||_|"  (all pipes in the eight)
    for (size_t i = 0; i < ACCOUNT_NUMBER_LEN; i++)
    {
        size_t num_index = (i / 3) % 9;
        size_t num_pipe_index = i % 3 + (3 * (i / 27));
        pipes[num_index][num_pipe_index] = account_number[i / COLS][i % COLS];
    }

    for (size_t i = 0; i < DIGITS_LEN; i++)
    {
        uint64_t hash = pipes_to_hash(pipes[i]);
        uint32_t digit = lookup_digit(hash);
        result_digits[i] = digit;
    }

    return NULL;
}

/**
 * Example:
 * account number:  3  4  5  8  8  2  8  6  5
 * position names:  d9 d8 d7 d6 d5 d4 d3 d2 d1
 *
 * checksum calculation:
 * (d1+2*d2+3*d3+...+9*d9) mod 11 = 0
 */
bool validate_checksum(uint8_t result_digits[DIGITS_LEN])
{
    if (NULL == result_digits)
    {
        return false;
    }

    uint32_t checksum = 0;
    for (size_t i = 0; i < DIGITS_LEN; i++)
    {
        uint8_t digit = result_digits[i];

        // Return false for any numbers containing invalid numbers.
        if (UINT8_MAX == digit)
        {
            return false;
        }

        checksum += digit * (DIGITS_LEN - i);
    }

    return checksum % 11 == 0;
}

/**
 * User Story 3 but doesn't print to a file, just return a formatted row.
 * The returned string is located on the heap, so it needs to be deallocated
 * by the caller.
 */
const char *to_file_format(uint8_t result_digits[DIGITS_LEN])
{
    if (NULL == result_digits)
    {
        return NULL;
    }

    // Max size of the formatted text is 13 characters + null terminator.
    char *result = malloc(13 + 1);

    // convert the numbers to characters and see if any illegal chars are found.
    bool contains_illegal_char = false;
    for (size_t i = 0; i < DIGITS_LEN; i++)
    {
        uint8_t digit = result_digits[i];

        // Any invalid digits should be converted to questionmarks.
        if (UINT8_MAX == digit)
        {
            result[i] = '?';
            contains_illegal_char = true;
        }
        else
        {
            result[i] = digit + '0';
        }
    }

    // Add any "error message" after the string if needed.
    if (contains_illegal_char)
    {
        const char ill[] = {' ', 'I', 'L', 'L', '\0'};
        for (int i = 0; i < sizeof(ill); i++)
        {
            result[i + DIGITS_LEN] = ill[i];
        }
    }
    else if (!validate_checksum(result_digits))
    {
        const char err[] = {' ', 'E', 'R', 'R', '\0'};
        for (int i = 0; i < sizeof(err); i++)
        {
            result[i + DIGITS_LEN] = err[i];
        }
    }
    else
    {
        result[DIGITS_LEN] = '\0';
    }

    return result;
}

// TODO: Doesn't give the correct results.
/**
 * Given a account number `digits`, returns all possible valid account numbers
 * that can be created by changing a single pipe in the input account number.
 * 
 * The result will be a heap allocation, so the caller needs to make sure to
 * free it. The dimension of the "array" in the result will be stored in the
 * argument `result_dim` so that the caller can see the result size. 
 */
uint8_t *correct(uint8_t digits[DIGITS_LEN], size_t *result_dim)
{
    if (NULL == digits || NULL == result_dim)
    {
        return NULL;
    }

    // Will contain the "corrected" account numbers if any is found.
    // Will be a heap pointer to imaginary arrays of results.
    uint8_t *result_digits = malloc(0);
    *result_dim = 0;

    // Contains digits that are currently being tested for validity i.e. a copy
    // of the `digits` array but with a single changed/"corrected" digit.
    uint8_t test_digits[DIGITS_LEN];

    // Will contain corrections for a single digit.
    uint8_t corrections[3] = {0};
    size_t corrections_dim = 0;

    // Iterates through all digits of the given input account number.
    for (size_t i = 0; i < DIGITS_LEN; i++)
    {
        // Returns != 0 on failure.
        uint64_t hash = lookup_hash(digits[i]);
        if (0 != lookup_corrections(hash, corrections, &corrections_dim))
        {
            return NULL;
        }

        memcpy(test_digits, digits, DIGITS_LEN);

        // Iterate through all corrections for this digit and test to see
        // if the correction is valid.
        for (int j = 0; j < corrections_dim; j++)
        {
            test_digits[i] = corrections[j];

            if (validate_checksum(test_digits))
            {
                // Add space to the results and copy the current `test_digits`
                // into the results (since it is a valid correction).
                result_digits = realloc(result_digits, (*result_dim + 1) * DIGITS_LEN);
                memcpy(result_digits + (*result_dim * DIGITS_LEN), test_digits, DIGITS_LEN);
                (*result_dim)++;
            }
        }
    }

    // If corrections are found, return them. Otherwise, make sure to free the
    // allocated `result_digits`. Might have been initialized, it is UB, but
    // always safe to call free even if it is NULL.
    if (0 < *result_dim)
    {
        return result_digits;
    }
    else
    {
        free(result_digits);
        return NULL;
    }
}

/**
 * Since there are no built in hashmap in C, this function is used to simulate
 * a hash function which takes in the characters and turns them into a unique
 * 64 bit int.
 * The ASCII characters will be truncated to 7 bits and are then put one after
 * another into a 64bit int.
 * 7 * 9 = 63, so the MSB will always be set to zero.
 * 
 * This hash will then be used to lookup what digit theses characters represents.
 */
static uint64_t pipes_to_hash(char digit[DIGIT_SIZE])
{
    uint64_t hash = 0;

    for (int i = 0; i < DIGIT_SIZE; i++)
    {
        uint64_t shift_amount = ((DIGIT_SIZE - i - 1) * 7);
        hash |= ((uint64_t)(digit[i] & 127)) << shift_amount;
    }

    return hash;
}

/**
 * Given a "hash" of the characters, return the number that it represents.
 */
static uint8_t lookup_digit(uint64_t hash)
{
    switch (hash)
    {
    case 0x20be83e20f9f2ffc:
        return 0;
    case 0x204081020f88107c:
        return 1;
    case 0x20be8105ff9f2fa0:
        return 2;
    case 0x20be8105ff882ffc:
        return 3;
    case 0x204083e5ff88107c:
        return 4;
    case 0x20be83e5f4082ffc:
        return 5;
    case 0x20be83e5f41f2ffc:
        return 6;
    case 0x20be81020f88107c:
        return 7;
    case 0x20be83e5ff9f2ffc:
        return 8;
    case 0x20be83e5ff882ffc:
        return 9;
    default:
        return UINT8_MAX;
    }
}

/**
 * Given a digit, returns the hash (reverse of "lookup_digit").
 */
static uint64_t lookup_hash(uint8_t digit)
{
    switch (digit)
    {
    case 0:
        return 0x20be83e20f9f2ffc;
    case 1:
        return 0x204081020f88107c;
    case 2:
        return 0x20be8105ff9f2fa0;
    case 3:
        return 0x20be8105ff882ffc;
    case 4:
        return 0x204083e5ff88107c;
    case 5:
        return 0x20be83e5f4082ffc;
    case 6:
        return 0x20be83e5f41f2ffc;
    case 7:
        return 0x20be81020f88107c;
    case 8:
        return 0x20be83e5ff9f2ffc;
    case 9:
        return 0x20be83e5ff882ffc;
    default:
        return 0;
    }
}

/**
 * Given a "hash" of the characters, returns the possible correction numbers i.e.
 * numbers that have a change of exactly one "pipe".
 * 
 * The result will be inserted into the given `corrections` parameter. Since the
 * max amount of corrections are 3 numbers, the given `corrections` needs to have
 * space for atleast three digits.
 * The size/dimension of the result corrections will be set in `corrections_dim`.
 * 
 * The returned int indicates if something has gone wronng. It will be set to 0
 * for success and any other number for failures.
 * 
 * 0 => 8
 * 1 => 7
 * 2, 3, 4 => null
 * 5 => 6, 9
 * 6, 9 => 5, 8
 * 7 => 1
 * 8 => 0, 6, 9
 */
static int lookup_corrections(uint64_t hash, uint8_t corrections[3], size_t *corrections_dim)
{
    if (NULL == corrections || NULL == corrections_dim)
    {
        return 1;
    }

    int resultCode = 0;

    switch (hash)
    {
    case 0x20be83e20f9f2ffc: // 0
        corrections[0] = 8;
        *corrections_dim = 1;
        break;
    case 0x204081020f88107c: // 1
        corrections[0] = 7;
        *corrections_dim = 1;
        break;
    case 0x20be8105ff9f2fa0: // 2
    case 0x20be8105ff882ffc: // 3
    case 0x204083e5ff88107c: // 4
        *corrections_dim = 0;
        break;
    case 0x20be83e5f4082ffc: // 5
        corrections[0] = 6;
        corrections[1] = 9;
        *corrections_dim = 2;
        break;
    case 0x20be83e5f41f2ffc: // 6
    case 0x20be83e5ff882ffc: // 9
        corrections[0] = 5;
        corrections[1] = 8;
        *corrections_dim = 2;
        break;
    case 0x20be81020f88107c: // 7
        corrections[0] = 1;
        *corrections_dim = 1;
        break;
    case 0x20be83e5ff9f2ffc: // 8
        corrections[0] = 0;
        corrections[1] = 6;
        corrections[2] = 9;
        *corrections_dim = 3;
        break;
    default:
        resultCode = 1;
        *corrections_dim = 0;
        break;
    }

    return resultCode;
}