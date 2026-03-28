#pragma once

typedef struct {
    int rows;
    int cols;
} window_size_t;

typedef struct {
    double step;
    double offset;
} cam_pos_t;

void update_window_size();
void draw_point(int x, int y, char c);
void get_window_size(window_size_t* w);

int cartesian_to_screen_x(double x, double step, double offset);
int cartesian_to_screen_y(double y, double step, double offset);
double screen_to_cartesian_x(double x, double step, double offset);
double screen_to_cartesian_y(double y, double step, double offset);
cam_pos_t screen_to_cam_pos(double left, double right, int window_size);