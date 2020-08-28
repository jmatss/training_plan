#include <stdbool.h>
#include <stdint.h>
#include "CU_main.h"
#include "CUnit/Basic.h"
#include "converter.h"

static void test_convert_zero_account_number(void);
static void test_convert_123456789_account_number(void);
static void test_convert_invalid_account_number_returns_u8_max(void);
static void test_convert_to_short_column_returns_error_msg(void);
static void test_convert_null_returns_error_msg(void);
static void test_validate_checksum_correctly(void);
static void test_validate_checksum_returns_false_for_invalid_account_number(void);
static void test_validate_checksum_returns_false_for_invalid_digit_in_account_number(void);
static void test_to_file_format_formats_valid_account_number_correctly();
static void test_to_file_format_adds_ERR_for_invalid_account_number();
static void test_to_file_format_adds_ILL_and_questionmark_for_illegal_number();

TEST_TABLE_START
TEST_TABLE_ENTRY(test_convert_zero_account_number)
TEST_TABLE_ENTRY(test_convert_123456789_account_number)
TEST_TABLE_ENTRY(test_convert_invalid_account_number_returns_u8_max)
TEST_TABLE_ENTRY(test_convert_to_short_column_returns_error_msg)
TEST_TABLE_ENTRY(test_convert_null_returns_error_msg)
TEST_TABLE_ENTRY(test_validate_checksum_correctly)
TEST_TABLE_ENTRY(test_validate_checksum_returns_false_for_invalid_account_number)
TEST_TABLE_ENTRY(test_validate_checksum_returns_false_for_invalid_digit_in_account_number)
TEST_TABLE_ENTRY(test_to_file_format_formats_valid_account_number_correctly)
TEST_TABLE_ENTRY(test_to_file_format_adds_ERR_for_invalid_account_number)
TEST_TABLE_ENTRY(test_to_file_format_adds_ILL_and_questionmark_for_illegal_number)
TEST_TABLE_END

INIT_TEST_SUITE("bankOCR test", NULL, NULL)

static void test_convert_zero_account_number()
{
    // ARRANGE
    uint8_t expected_account_number[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    const char *account_number_input[3] = {
        " _  _  _  _  _  _  _  _  _ ",
        "| || || || || || || || || |",
        "|_||_||_||_||_||_||_||_||_|"};

    // ACT
    uint8_t actual_account_number[9];
    convert(account_number_input, actual_account_number);

    // ASSERT
    CU_ASSERT_EQUAL(0, memcmp(actual_account_number, expected_account_number, 9));
}

static void test_convert_123456789_account_number()
{
    // ARRANGE
    uint8_t expected_account_number[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    const char *account_number_input[3] = {
        "    _  _     _  _  _  _  _ ",
        "  | _| _||_||_ |_   ||_||_|",
        "  ||_  _|  | _||_|  ||_| _|"};

    // ACT
    uint8_t actual_account_number[9];
    convert(account_number_input, actual_account_number);

    // ASSERT
    CU_ASSERT_EQUAL(0, memcmp(actual_account_number, expected_account_number, 9));
}

static void test_convert_invalid_account_number_returns_u8_max()
{
    // ARRANGE
    uint8_t expected_account_number[9] = {UINT8_MAX, 2, 3, 4, 5, 6, 7, 8, 9};
    const char *account_number_input[3] = {
        "    _  _     _  _  _  _  _ ",
        "ab| _| _||_||_ |_   ||_||_|",
        "  ||_  _|  | _||_|  ||_| _|"};

    // ACT
    uint8_t actual_account_number[9];
    convert(account_number_input, actual_account_number);

    // ASSERT
    CU_ASSERT_EQUAL(0, memcmp(actual_account_number, expected_account_number, 9));
}

static void test_convert_to_short_column_returns_error_msg()
{
    // ARRANGE
    const char *account_number_input[3] = {
        "    _  _     ",
        "  | _| _||_||_ |_   ||_||_|",
        "  ||_  _|  | _||_|  ||_| _|"};

    // ACT
    const char *actual_result = convert(account_number_input, NULL);

    // ASSERT
    CU_ASSERT_PTR_NOT_NULL(actual_result);
}

static void test_convert_null_returns_error_msg()
{
    // ARRANGE & ACT
    const char *actual_result = convert(NULL, NULL);

    // ASSERT
    CU_ASSERT_PTR_NOT_NULL(actual_result);
}

static void test_validate_checksum_correctly()
{
    // ARRANGE
    uint8_t valid_account_number[9] = {3, 4, 5, 8, 8, 2, 8, 6, 5};

    // ACT
    bool actual_result = validate_checksum(valid_account_number);

    // ASSERT
    CU_ASSERT_TRUE(actual_result);
}

static void test_validate_checksum_returns_false_for_invalid_account_number()
{
    // ARRANGE
    uint8_t valid_account_number[9] = {0, 4, 5, 8, 8, 2, 8, 6, 5};

    // ACT
    bool actual_result = validate_checksum(valid_account_number);

    // ASSERT
    CU_ASSERT_FALSE(actual_result);
}

static void test_validate_checksum_returns_false_for_invalid_digit_in_account_number()
{
    // ARRANGE
    uint8_t valid_account_number[9] = {3, UINT8_MAX, 5, 8, 8, 2, 8, 6, 5};

    // ACT
    bool actual_result = validate_checksum(valid_account_number);

    // ASSERT
    CU_ASSERT_FALSE(actual_result);
}

static void test_to_file_format_formats_valid_account_number_correctly()
{
    // ARRANGE
    uint8_t valid_account_number[9] = {3, 4, 5, 8, 8, 2, 8, 6, 5};
    const char *expected_result = "345882865";

    // ACT
    const char *actual_result = to_file_format(valid_account_number);

    // ASSERT
    CU_ASSERT_STRING_EQUAL(actual_result, expected_result);
}

static void test_to_file_format_adds_ERR_for_invalid_account_number()
{
    // ARRANGE
    uint8_t invalid_account_number[9] = {0, 4, 5, 8, 8, 2, 8, 6, 5};
    const char *expected_result = "045882865 ERR";

    // ACT
    const char *actual_result = to_file_format(invalid_account_number);

    // ASSERT
    CU_ASSERT_STRING_EQUAL(actual_result, expected_result);
}

static void test_to_file_format_adds_ILL_and_questionmark_for_illegal_number()
{
    // ARRANGE
    uint8_t invalid_account_number[9] = {3, UINT8_MAX, 5, 8, 8, 2, 8, 6, 5};
    const char *expected_result = "3?5882865 ILL";

    // ACT
    const char *actual_result = to_file_format(invalid_account_number);

    // ASSERT
    CU_ASSERT_STRING_EQUAL(actual_result, expected_result);
}
