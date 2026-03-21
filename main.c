#include <math.h>
#include <stdio.h>
#include <unistd.h>

#include "codes.h"
#include "screen.h"

void init() {
    setbuf(stdout, NULL);
    update_window_size();
    printf(ENABLE_ALT_BUFFER ERASE_SCREEN HIDE_CURSOR DISABLE_LINE_WRAP);
}

void deinit() {
    printf(ERASE_SCREEN DISABLE_ALT_BUFFER ENABLE_LINE_WRAP SHOW_CURSOR);
}

int f(int x) { return x * x + 1; }

int main() {
    init();

    int x_offset = 0;
    int y_offset = 5;

    int x_zoom = 10;
    int y_zoom = 1;

    // draw out x and y axis
    window_size_t w;
    get_window_size(&w);

    int x_axis_row = cartesian_to_screen_y(0, y_zoom, y_offset);
    int y_axis_col = cartesian_to_screen_x(0, x_zoom, x_offset);

    for (int col = 0; col < w.cols; col++) draw_point(col, x_axis_row, '-');
    for (int row = 0; row < w.rows; row++) draw_point(y_axis_col, row, '|');

    // plot out f(x)
    for (int x = -10; x < 10; x++) {
        draw_point(cartesian_to_screen_x(x, x_zoom, x_offset),
                   cartesian_to_screen_y(f(x), y_zoom, y_offset), '*');
    }
    sleep(5);

    deinit();
    return 0;
}
