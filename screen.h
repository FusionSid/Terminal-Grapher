#pragma once

typedef struct {
    int rows;
    int cols;
} window_size_t;

void update_window_size();
void draw_point(int x, int y, char c);
void get_window_size(window_size_t* w);

int cartesian_to_screen_x(int x, int zoom, int offset);
int cartesian_to_screen_y(int y, int zoom, int offset);
int screen_to_cartesian_x(int x, int zoom, int offset);
int screen_to_cartesian_y(int y, int zoom, int offset);
