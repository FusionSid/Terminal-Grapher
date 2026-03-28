
#include "render.h"

#include <stdio.h>
#include <unistd.h>

#include "codes.h"

void plot_axes(window_size_t w, render_state_t* state) {
    int x_axis_row = cartesian_to_screen_y(0, state->y_step, state->y_offset);
    int y_axis_col = cartesian_to_screen_x(0, state->x_step, state->x_offset);

    for (int col = 0; col < w.cols; col++) draw_point(col, x_axis_row, '-');
    for (int row = 0; row < w.rows; row++) draw_point(y_axis_col, row, '|');
}

void plot_function(window_size_t w, render_state_t* state, ast_node_t* node,
                   int delay) {
    double left_bound =
        screen_to_cartesian_x(0, state->x_step, state->x_offset);
    double right_bound =
        screen_to_cartesian_x(w.cols, state->x_step, state->x_offset);

    for (double x = left_bound; x < right_bound; x += state->x_step) {
        double y_at_x = ast_evaluate(node, x);

        draw_point(
            cartesian_to_screen_x(x, state->x_step, state->x_offset),
            cartesian_to_screen_y(y_at_x, state->y_step, state->y_offset), '*');
        if (delay) usleep(delay);
    }
}

void render(window_size_t w, render_state_t* state, ast_node_t* node,
            int delay) {
    printf(ERASE_SCREEN);
    plot_axes(w, state);
    plot_function(w, state, node, delay);
}
