#include "input.h"

bool apply_action(render_state_t* state, char c) {
    switch (c) {
        case 'w':  // up
            state->y_offset += 0.5;
            break;
        case 'a':  // left
            state->x_offset += 0.5;
            break;
        case 's':  // down
            state->y_offset -= 0.5;
            break;
        case 'd':  // right
            state->x_offset -= 0.5;
            break;

        case '-':  // zoom in x
            state->x_step *= 1.1;
            break;
        case '=':  // zoom out x
            state->x_step *= 0.9;
            break;
        case 'o':  // zoom out y
            state->y_step *= 1.1;
            break;
        case 'i':  // zoom in y
            state->y_step *= 0.9;
            break;

        case 'r':  // reset
            state->x_offset = DEFAULT_X_OFFSET;
            state->y_offset = DEFAULT_Y_OFFSET;
            state->x_step = DEFAULT_X_STEP;
            state->y_step = DEFAULT_Y_STEP;
            break;

        default:
            return false;
    }

    return true;
}