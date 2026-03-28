#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "codes.h"
#include "input.h"
#include "render.h"
#include "screen.h"
#include "term.h"

// this is the func (slang for function btw) imma plot
float f(float x) { return 10 * sin(x - 2) * cos(2 * x); }
// float f(float x) { return sin(x); }
// float f(float x) { return x*x; }

int main() {
    init();
    enable_raw_mode();

    window_size_t w;
    get_window_size(&w);

    render_state_t render_state = {
        .x_offset = DEFAULT_X_OFFSET,
        .y_offset = DEFAULT_Y_OFFSET,
        .x_step = DEFAULT_X_STEP,
        .y_step = DEFAULT_Y_STEP,
    };
    render(w, &render_state, f,
           5000);  // initaly use non zero delay to animate drawing the function

    char c;
    while (1) {
        if (read(STDIN_FILENO, &c, 1) != 1) continue;

        if (c == 'q') break;

        if (apply_action(&render_state, c)) {
            render(w, &render_state, f, 0);
        }
    }

    deinit();
    return 0;
}
