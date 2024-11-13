#include "base.h"
#include "log.h"

#define ROWS 4
#define COLS 4

enum {
    DIR_RIGHT = 0,
    DIR_DOWN  = 1,
    DIR_LEFT  = 2,
    DIR_UP    = 3,
};

// NOTE(nix3l): i could do this in a fancy way
//              with modulus and stuff but it
//              doesnt really matter and this is more readable
//              probably also faster on most compilers
i32 step_on_turn(u32 dir) {
    if(dir == DIR_RIGHT) // turning down
        return COLS;
    if(dir == DIR_DOWN) // turning left
        return -1;
    if(dir == DIR_LEFT) // turning up 
        return -COLS;
    if(dir == DIR_UP) // turning right
        return 1;

    LOG_ERR("wtf\n");
    return 0;
}

int main(void) {
    u32 data[ROWS * COLS] = {0};

    u32 pivot = 0;
    u32 offset = 0;
    u32 elements_in_cycle = COLS;
    u32 num_half_turns = 0; // half turns are counted on the verticals (turning up/down)
    u32 dir = DIR_RIGHT;
    i32 step = 1;
    for(u32 elem = 0; elem < ROWS * COLS; elem ++) {
        u32 index = pivot + offset * step;
        data[index] = elem + 1;
        offset ++;

        // turn whenever we reach an edge
        if(offset % elements_in_cycle == 0) {
            // get the next step
            step = step_on_turn(dir);
            // turn and get the amount of elements in the cycle
            dir = (dir + 1) % 4;
            if(dir == DIR_DOWN || dir == DIR_UP) num_half_turns ++;
            elements_in_cycle = dir % 2 == 0 ? COLS - num_half_turns: ROWS - num_half_turns;
            // move the pivot to the new index and reset the offset
            pivot = index + step;
            offset = 0;
        }
    }

    // show the data
    for(u32 i = 0; i < ROWS; i ++) {
        for(u32 j = 0; j < COLS; j ++) {
            LOG("%u ", data[i * ROWS + j]);
        }
        LOG("\n");
    }

    return 0;
}
