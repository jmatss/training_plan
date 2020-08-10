#include <stddef.h>
#include "bowling.h"

static void bowling_update_bonus(BowlingState *state, int pins);

#define MAX_FRAMES 10
#define MAX_PINS 10

/**
 * Sets the initial values. The callee will create the "BowlingState" before
 * calling this function, this only resets/initializes the values.
 */
void bowling_init(BowlingState *state)
{
    state->frame = 1;
    state->frame_score = 0;
    state->total_score = 0;
    state->throw_count = FIRST;
    state->bonus[0] = 0;
    state->bonus[1] = 0;
    state->finished = false;
}

/**
 * Registers a new roll.
 * 
 * Returns NULL if the roll was valid.
 * Returns a value != NULL if the score for the current frame is invalid, either
 * because the given argument `pins` exceeds 10, because the total amount of
 * knocked down pins for the current frame exceeds 10 or because the game is
 * already finished.
 */
const char *bowling_roll(BowlingState *state, int pins)
{
    if (MAX_PINS < pins)
    {
        return "The given `pins` argument is greater than 10";
    }
    else if (MAX_PINS < state->frame_score + pins)
    {
        return "The amount of knocked down pins for the current frame exceedes 10.";
    }
    else if (bowling_is_finished(state))
    {
        return "The game has already finished.";
    }

    state->frame_score += pins;

    bowling_update_bonus(state, pins);

    // If true: All ten pins knocked down for the current frame.
    // Else: Some pins left standing.
    if (MAX_PINS == state->frame_score)
    {
        // If this is isn't the last frame or isn't the third throw of the last
        // frame, the frame should be incremented and the `throw_count` should
        // be restarted. Otherwise, if this is the last frame and either the
        // first or second throw, the player should get a extra throw since they
        // knocked down all pins.
        if (MAX_FRAMES != state->frame || THIRD == state->throw_count)
        {
            state->throw_count = FIRST;
            state->frame++;
        }
        else  // First or second throw on the last frame.
        {
            state->throw_count++;
        }
        state->total_score += state->frame_score;
        state->frame_score = 0;
    }
    else
    {
        // If this is the second or third throw and the player haven't knocked
        // down all pins, it is time to add the frame score to the total score
        // and go to the next frame.
        switch (state->throw_count)
        {
        case SECOND:
        case THIRD:
            state->total_score += state->frame_score;
            state->frame++;
            state->frame_score = 0;
            state->throw_count = FIRST;
            break;

        case FIRST:
            state->throw_count++;
            break;
        }
    }

    if (MAX_FRAMES < state->frame)
    {
        state->finished = true;
    }

    // Return null indicating success (?).
    return NULL;
}

int bowling_score(BowlingState *state)
{
    return state->total_score;
}

bool bowling_is_finished(BowlingState *state)
{
    return state->finished;
}

/**
 * Add bonus from previous spares and strikes to the `total_score` and then shift
 * the values in the bonus array to the left indicating that a "throw has passed".
 */
static void bowling_update_bonus(BowlingState *state, int pins)
{
    // Add the spare/strike bonus from previous throw to the total score for the
    // current throw and then shift the values in the `bonus` array to the left
    // to prepare the bonus for the next throw. 
    if (0 < state->bonus[0])
    {
        state->total_score += (state->bonus[0] * pins);
    }
    state->bonus[0] = state->bonus[1];
    state->bonus[1] = 0;

    // If the current throw takes down all pins for the current frame
    // and it isn't the last frame, set indicators to the "next throws"
    // about spare/strike bonuses that needs to be added to the `total_score`.
    if (MAX_PINS == state->frame_score && MAX_FRAMES != state->frame)
    {
        if (SECOND == state->throw_count)
        {
            // Add bonus count for spare.
            state->bonus[0]++;
        }
        else if (FIRST == state->throw_count)
        {
            // Add bonus count for strike.
            state->bonus[0]++;
            state->bonus[1]++;
        }
    }
}