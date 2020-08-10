#ifndef BOWLING_H_
#define BOWLING_H_

#include <stdbool.h>

/**
 * What throw it is in the current throw.
 * A third can only be done at the last frame (if one gets down all pins).
 */
typedef enum
{
    FIRST = 0,
    SECOND = 1,
    THIRD = 2,
} Throw;

typedef struct BowlingState
{
    // The current frame (aka. the current round).
    // Starts at 1 and ends at frame 10.
    int frame;

    // Keeps track of the score for the current frame (max 10).
    int frame_score;

    // Keeps track of the current total score (counting all previous frames).
    int total_score;

    // The current throw in the frame (1, 2 ,3).
    Throw throw_count;

    // The variable stores information about strikes and spared from previous
    // frames.
    // If a throw is a spare, the value at index "0" shhould be incremented.
    // If a throw is a strike, both values should be incremented.
    //
    // The value at index "0" indicates how many times the current throw should
    // be added to the `total_score` (bonus for spare/strike). The value at
    // index "1" indicates how many times the NEXT throw should be added to the
    // `total_score`. After every throw the values in the array will be
    // "shifted to the left" and the value at index "1" (last index) will be
    // reset to 0 before the current throws bonus is added.
    //
    // Example:
    // {0, 0} -> STRIKE -> {1, 1} -> STRIKE -> {2, 1} -> NOTHING -> {1, 0}
    int bonus[2];

    // Indicates if the game is finished.
    bool finished;
} BowlingState;

void bowling_init(BowlingState *state);
const char *bowling_roll(BowlingState *state, int pins);
int bowling_score(BowlingState *state);
bool bowling_is_finished(BowlingState *state);

#endif /* BOWLING_H_ */
