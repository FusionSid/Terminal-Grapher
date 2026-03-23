#include <math.h>
#include <stdio.h>
#include <unistd.h>

#include "codes.h"
#include "screen.h"

void init();
void deinit();
void plot_function(window_size_t w, float x_step, float y_step, float x_offset,
                   float y_offset, float (*f)(float), int delay);
void plot_axes(window_size_t w, float x_step, float y_step, float x_offset,
               float y_offset);

float f1(float x) { return x * x + 1; }
float f2(float x) { return 10 * sin(x - 2) * cos(2 * x); }

int main() {
    init();

    // can easily calculate x or y step as domain/w.cols or range/w.rows
    int x_offset = 0;
    int y_offset = 13;
    float x_step = 0.06;
    float y_step = 0.2;

    window_size_t w;
    get_window_size(&w);

    plot_axes(w, x_step, y_step, x_offset, y_offset);
    plot_function(w, x_step, y_step, x_offset, y_offset, f1, 0);
    sleep(1);
    printf(ERASE_SCREEN);

    y_offset = 0;
    x_step = 0.05;
    y_step = 1.3;

    plot_axes(w, x_step, y_step, x_offset, y_offset);
    plot_function(w, x_step, y_step, x_offset, y_offset, f2, 5000);
    sleep(5);
    printf(ERASE_SCREEN);

    deinit();
    return 0;
}

void init() {
    setbuf(stdout, NULL);
    update_window_size();
    printf(ENABLE_ALT_BUFFER ERASE_SCREEN HIDE_CURSOR DISABLE_LINE_WRAP);
}

void deinit() {
    printf(ERASE_SCREEN DISABLE_ALT_BUFFER ENABLE_LINE_WRAP SHOW_CURSOR);
}

void plot_axes(window_size_t w, float x_step, float y_step, float x_offset,
               float y_offset) {
    int x_axis_row = cartesian_to_screen_y(0, y_step, y_offset);
    int y_axis_col = cartesian_to_screen_x(0, x_step, x_offset);

    for (int col = 0; col < w.cols; col++) draw_point(col, x_axis_row, '-');
    for (int row = 0; row < w.rows; row++) draw_point(y_axis_col, row, '|');
}

void plot_function(window_size_t w, float x_step, float y_step, float x_offset,
                   float y_offset, float (*f)(float), int delay) {
    int left_bound = screen_to_cartesian_x(0, x_step, x_offset);
    int right_bound = screen_to_cartesian_x(w.cols, x_step, x_offset);

    for (float x = left_bound; x < right_bound; x += x_step) {
        draw_point(cartesian_to_screen_x(x, x_step, x_offset),
                   cartesian_to_screen_y(f(x), y_step, y_offset), '*');
        usleep(delay);
    }
}