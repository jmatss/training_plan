#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <stdint.h>

#define ROWS ((size_t)3)
#define COLS ((size_t)27)
#define ACCOUNT_NUMBER_LEN ((size_t)(COLS * ROWS))

// Amount of digits in a account number.
#define DIGITS_LEN ((size_t)9)

// Amount of pipes (underscore/pipe/whitespace) that makes up a digit.
#define DIGIT_SIZE ((size_t)9)

const char *convert(const char *account_number[ROWS], uint8_t result_digits[DIGITS_LEN]);
bool validate_checksum(uint8_t result_digits[DIGITS_LEN]);
const char *to_file_format(uint8_t result_digits[DIGITS_LEN]);
uint8_t *correct(uint8_t digits[DIGITS_LEN], size_t *result_dim);

#endif /* CONVERTER_H_ */
