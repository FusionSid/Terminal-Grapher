#pragma once

typedef struct {
    int rows;
    int cols;
} window_size_t;

void update_window_size();
void draw_point(int x, int y, char c);
void get_window_size(window_size_t* w);

int cartesian_to_screen_x(float x, float step, float offset);
int cartesian_to_screen_y(float y, float step, float offset);
float screen_to_cartesian_x(float x, float step, float offset);
float screen_to_cartesian_y(float y, float step, float offset);