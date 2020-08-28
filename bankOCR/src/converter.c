#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "converter.h"

static uint64_t chars_to_hash(char digit[DIGIT_SIZE]);
static uint8_t lookup_digit(uint64_t hash);

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
 * Lookup for possible correction digits with only a single removed/added line.
 * Ex. a zero could be a eight that just have lost its middle line.
 */
/* TODO: User Story 4
const static uint8_t *Abc[10] = {
    {8},       // 0
    {7},       // 1
    NULL,      // 2
    NULL,      // 3
    NULL,      // 4
    {6, 9},    // 5
    {5, 8},    // 6
    {1},       // 7
    {0, 6, 9}, // 8
    {5, 8}     // 9
};
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

    char digits[9][DIGIT_SIZE];

    for (size_t i = 0; i < ACCOUNT_NUMBER_LEN; i++)
    {
        size_t num_index = (i / 3) % 9;
        size_t num_digit = i % 3 + (3 * (i / 27));
        digits[num_index][num_digit] = account_number[i / COLS][i % COLS];
    }

    for (size_t i = 0; i < DIGITS_LEN; i++)
    {
        uint64_t hash = chars_to_hash(digits[i]);
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

/* TODO: User Story 4
uint8_t **correct(uint8_t digits[DIGITS_LEN])
{

}
*/

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
static uint64_t chars_to_hash(char digit[DIGIT_SIZE])
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