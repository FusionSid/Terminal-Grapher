#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "codes.h"
#include "screen.h"

void init();
void enable_raw_mode();

void deinit();
void disable_raw_mode();

void plot_function(window_size_t w, float x_step, float y_step, float x_offset,
                   float y_offset, float (*f)(float), int delay);
void plot_axes(window_size_t w, float x_step, float y_step, float x_offset,
               float y_offset);

// this is the func (slang for function btw) imma plot
float f(float x) { return 10 * sin(x - 2) * cos(2 * x); }
// float f(float x) { return sin(x); }
// float f(float x) { return x*x; }

struct termios orig_termios;

int main() {
    init();
    enable_raw_mode();

    window_size_t w;
    get_window_size(&w);

    float x_offset = 0;
    float y_offset = 0;
    float x_step = 0.05;
    float y_step = 0.5;

    plot_axes(w, x_step, y_step, x_offset, y_offset);
    plot_function(w, x_step, y_step, x_offset, y_offset, f, 5000);

    char c;
    while (1) {
        int n = read(STDIN_FILENO, &c, 1);
        if (n != 1) continue;

        if (c == 'q')
            break;

        else if (c == 'w')  // up
            y_offset += 0.5;
        else if (c == 'a')  // left
            x_offset -= 0.5;
        else if (c == 's')  // down
            y_offset -= 0.5;
        else if (c == 'd')  // right
            x_offset += 0.5;

        else if (c == '-')  // zoom in x
            x_step *= 1.1;
        else if (c == '=')  // zoom out x
            x_step *= 0.9;
        else if (c == 'o')  // zoom out y
            y_step *= 1.1;
        else if (c == 'i')  // zoom in y
            y_step *= 0.9;

        else if (c == 'r') {  // reset
            x_offset = 0;
            y_offset = 0;
            x_step = 0.05;
            y_step = 0.5;
        }

        else
            continue;

        // if we here, we must have pressed smth that requires a replot of f(x)
        printf(ERASE_SCREEN);
        plot_axes(w, x_step, y_step, x_offset, y_offset);
        plot_function(w, x_step, y_step, x_offset, y_offset, f, 0);
    }

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

void disable_raw_mode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); }

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);

    struct termios raw = orig_termios;

    // echo is stops the terminal from printing when you type smth
    // canonical allows you to input without needing to press enter
    raw.c_lflag &= ~(ECHO | ICANON);  // turn off echo and canonical
    raw.c_cc[VMIN] = 0;               // min bytes to read
    raw.c_cc[VTIME] = 1;              // timeout in 1/10 of a sec

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}