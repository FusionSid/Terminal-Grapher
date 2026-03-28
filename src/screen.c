
#include "screen.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

static window_size_t window_data;

void update_window_size() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    window_data.rows = w.ws_row;
    window_data.cols = w.ws_col;
}

void get_window_size(window_size_t* w) {
    memcpy(w, &window_data, sizeof(window_size_t));
}

void draw_point(int x, int y, char c) {
    if (x < 0 || y < 0 || x >= window_data.cols || y >= window_data.rows)
        return;

    printf("\x1b[%i;%iH%c", y + 1, x + 1, c);
}

int cartesian_to_screen_x(double x, double step, double offset) {
    double zoom = 1 / step;
    return zoom * x + window_data.cols / 2 + offset;
}

int cartesian_to_screen_y(double y, double step, double offset) {
    double zoom = 1 / step;
    return window_data.rows / 2 - zoom * y + offset;
}

double screen_to_cartesian_x(double x, double step, double offset) {
    double zoom = 1 / step;
    return (x - offset - window_data.cols / 2) / zoom;
}

double screen_to_cartesian_y(double y, double step, double offset) {
    double zoom = 1 / step;
    return (window_data.rows / 2 - y + offset) / zoom;
}

cam_pos_t screen_to_cam_pos(double left, double right, int window_size) {
    double total_distance = fabs(right - left);

    cam_pos_t cam_pos = {.step = window_size / total_distance,
                         .offset = total_distance / 2};

    return cam_pos;
}
