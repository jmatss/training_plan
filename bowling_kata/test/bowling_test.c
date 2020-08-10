#include <stddef.h>
#include "CUnit/Basic.h"
#include "CU_main.h"
#include "bowling.h"

static void test_frame_incremented_after_strike();
static void test_frame_incremented_after_spare();
static void test_frame_incremented_after_frame_lower_than_10();
static void test_score_set_correctly_after_strike();
static void test_score_set_correctly_after_spare();
static void test_score_set_correctly_after_frame_lower_than_10();
static void test_strike_gives_bonus_for_two_extra_throws();
static void test_spare_gives_bonus_for_one_extra_throw();
static void test_frame_lower_than_10_does_not_give_bonus();
static void test_receives_error_if_more_than_10_pins_knocked_down_in_one_throw();
static void test_receives_error_if_more_than_10_pins_knocked_down_in_one_frame();
static void test_receives_error_if_more_than_10_frames_played();
static void test_bowl_perfect_round_gives_300_points();

TEST_TABLE_START
    TEST_TABLE_ENTRY(test_frame_incremented_after_strike)
    TEST_TABLE_ENTRY(test_frame_incremented_after_spare)
    TEST_TABLE_ENTRY(test_frame_incremented_after_frame_lower_than_10)
    TEST_TABLE_ENTRY(test_score_set_correctly_after_strike)
    TEST_TABLE_ENTRY(test_score_set_correctly_after_spare)
    TEST_TABLE_ENTRY(test_score_set_correctly_after_frame_lower_than_10)
    TEST_TABLE_ENTRY(test_strike_gives_bonus_for_two_extra_throws)
    TEST_TABLE_ENTRY(test_spare_gives_bonus_for_one_extra_throw)
    TEST_TABLE_ENTRY(test_frame_lower_than_10_does_not_give_bonus)
    TEST_TABLE_ENTRY(test_receives_error_if_more_than_10_pins_knocked_down_in_one_throw)
    TEST_TABLE_ENTRY(test_receives_error_if_more_than_10_pins_knocked_down_in_one_frame)
    TEST_TABLE_ENTRY(test_receives_error_if_more_than_10_frames_played)
    TEST_TABLE_ENTRY(test_bowl_perfect_round_gives_300_points)
TEST_TABLE_END

INIT_TEST_SUITE("Bowling test", NULL, NULL)

static void test_frame_incremented_after_strike()
{
    // ARRANGE
    int first_throw = 10;
    int expected_frame = 2;

    BowlingState state;
    bowling_init(&state);

    // ACT
    bowling_roll(&state, first_throw);
    int actualFrame = state.frame;

    // ASSERT
    CU_ASSERT_EQUAL(actualFrame, expected_frame);
}

static void test_frame_incremented_after_spare()
{
    // ARRANGE
    int first_throw = 4;
    int second_throw = 6;
    int expected_frame = 2;

    BowlingState state;
    bowling_init(&state);

    // ACT
    bowling_roll(&state, first_throw);
    bowling_roll(&state, second_throw);
    int actualFrame = state.frame;

    // ASSERT
    CU_ASSERT_EQUAL(actualFrame, expected_frame);
}

static void test_frame_incremented_after_frame_lower_than_10()
{
    // ARRANGE
    int first_throw = 0;
    int second_throw = 1;
    int expected_frame = 2;

    BowlingState state;
    bowling_init(&state);

    // ACT
    bowling_roll(&state, first_throw);
    bowling_roll(&state, second_throw);
    int actualFrame = state.frame;

    // ASSERT
    CU_ASSERT_EQUAL(actualFrame, expected_frame);
}

static void test_score_set_correctly_after_strike()
{
    // ARRANGE
    int first_throw = 10;
    int expected_score = first_throw;

    BowlingState state;
    bowling_init(&state);

    // ACT
    bowling_roll(&state, first_throw);
    int actual_score = state.total_score;

    // ASSERT
    CU_ASSERT_EQUAL(actual_score, expected_score);
}

static void test_score_set_correctly_after_spare()
{
    // ARRANGE
    int first_throw = 4;
    int second_throw = 6;
    int expected_score = first_throw + second_throw;

    BowlingState state;
    bowling_init(&state);

    // ACT
    bowling_roll(&state, first_throw);
    bowling_roll(&state, second_throw);
    int actual_score = state.total_score;

    // ASSERT
    CU_ASSERT_EQUAL(actual_score, expected_score);
}

static void test_score_set_correctly_after_frame_lower_than_10()
{
    // ARRANGE
    int first_throw = 0;
    int second_throw = 1;
    int expected_score = first_throw + second_throw;

    BowlingState state;
    bowling_init(&state);

    // ACT
    bowling_roll(&state, first_throw);
    bowling_roll(&state, second_throw);
    int actual_score = state.total_score;

    // ASSERT
    CU_ASSERT_EQUAL(actual_score, expected_score);
}

static void test_strike_gives_bonus_for_two_extra_throws()
{
    // ARRANGE
    int first_throw = 10;
    int second_throw = 1;
    int third_throw = 2;
    int fourth_throw = 10;
    int expected_score = first_throw + (2 * second_throw) + (2 * third_throw) + fourth_throw;

    BowlingState state;
    bowling_init(&state);

    // ACT
    bowling_roll(&state, first_throw);
    bowling_roll(&state, second_throw);
    bowling_roll(&state, third_throw);
    bowling_roll(&state, fourth_throw);
    int actual_score = state.total_score;

    // ASSERT
    CU_ASSERT_EQUAL(actual_score, expected_score);
}

static void test_spare_gives_bonus_for_one_extra_throw()
{
    // ARRANGE
    int first_throw = 4;
    int second_throw = 6;
    int third_throw = 3;
    int fourth_throw = 4;
    int expected_score = first_throw + second_throw + (2 * third_throw) + fourth_throw;

    BowlingState state;
    bowling_init(&state);

    // ACT
    bowling_roll(&state, first_throw);
    bowling_roll(&state, second_throw);
    bowling_roll(&state, third_throw);
    bowling_roll(&state, fourth_throw);
    int actual_score = state.total_score;

    // ASSERT
    CU_ASSERT_EQUAL(actual_score, expected_score);
}

static void test_frame_lower_than_10_does_not_give_bonus()
{
    // ARRANGE
    int first_throw = 0;
    int second_throw = 1;
    int third_throw = 10;
    int expected_score = first_throw + second_throw + third_throw;

    BowlingState state;
    bowling_init(&state);

    // ACT
    bowling_roll(&state, first_throw);
    bowling_roll(&state, second_throw);
    bowling_roll(&state, third_throw);
    int actual_score = state.total_score;

    // ASSERT
    CU_ASSERT_EQUAL(actual_score, expected_score);
}

static void test_receives_error_if_more_than_10_pins_knocked_down_in_one_throw()
{
    // ARRANGE
    int first_throw = 11;

    BowlingState state;
    bowling_init(&state);

    // ACT
    const char *res = bowling_roll(&state, first_throw);

    // ASSERT
    CU_ASSERT_PTR_NOT_NULL(res);
}

static void test_receives_error_if_more_than_10_pins_knocked_down_in_one_frame()
{
    // ARRANGE
    int first_throw = 5;
    int second_throw = 6;

    BowlingState state;
    bowling_init(&state);

    // ACT
    bowling_roll(&state, first_throw);
    const char *res = bowling_roll(&state, second_throw);

    // ASSERT
    CU_ASSERT_PTR_NOT_NULL(res);
}

static void test_receives_error_if_more_than_10_frames_played()
{
    // ARRANGE
    // There are 10 frames plus the player might be allowed to throw two extra
    // throws at the last frame. After 12 strikes, the game should be over.
    int iterations = 12;
    int strike_throw = 10;

    BowlingState state;
    bowling_init(&state);

    // ACT
    const char *res;
    for (int i = 0; i < iterations; i++)
    {
        res = bowling_roll(&state, strike_throw);
        CU_ASSERT_PTR_NULL(res);
    }

    res = bowling_roll(&state, strike_throw);

    // ASSERT
    CU_ASSERT_PTR_NOT_NULL(res);
}

static void test_bowl_perfect_round_gives_300_points()
{
    // ARRANGE
    // There are 10 frames plus the player might be allowed to throw two extra
    // throws at the last frame. After 12 strikes, the game should be over.
    int iterations = 12;
    int strike_throw = 10;
    int expected_result = 300;

    BowlingState state;
    bowling_init(&state);

    // ACT
    for (int i = 0; i < iterations; i++)
    {
        bowling_roll(&state, strike_throw);
    }
    int actual_result = bowling_score(&state);

    // ASSERT
    CU_ASSERT_TRUE(bowling_is_finished(&state));
    CU_ASSERT_EQUAL(actual_result, expected_result)
}