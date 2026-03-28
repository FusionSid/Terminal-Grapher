#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "codes.h"
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
        .x_offset = 0,
        .y_offset = 0,
        .x_step = 0.05,
        .y_step = 0.5,
    };

    plot_axes(w, &render_state);
    plot_function(w, &render_state, f, 5000);

    char c;
    while (1) {
        int n = read(STDIN_FILENO, &c, 1);
        if (n != 1) continue;

        if (c == 'q')
            break;

        else if (c == 'w')  // up
            render_state.y_offset += 0.5;
        else if (c == 'a')  // left
            render_state.x_offset += 0.5;
        else if (c == 's')  // down
            render_state.y_offset -= 0.5;
        else if (c == 'd')  // right
            render_state.x_offset -= 0.5;

        else if (c == '-')  // zoom in x
            render_state.x_step *= 1.1;
        else if (c == '=')  // zoom out x
            render_state.x_step *= 0.9;
        else if (c == 'o')  // zoom out y
            render_state.y_step *= 1.1;
        else if (c == 'i')  // zoom in y
            render_state.y_step *= 0.9;

        else if (c == 'r') {  // reset
            render_state.x_offset = 0;
            render_state.y_offset = 0;
            render_state.x_step = 0.05;
            render_state.y_step = 0.5;
        }

        else
            continue;

        // if we here, we must have pressed smth that requires a replot of f(x)
        printf(ERASE_SCREEN);
        plot_axes(w, &render_state);
        plot_function(w, &render_state, f, 0);
    }

    printf(ERASE_SCREEN);
    deinit();

    return 0;
}
