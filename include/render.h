#pragma once

#include "screen.h"

typedef struct {
    float x_offset, y_offset;
    float x_step, y_step;
} render_state_t;

typedef float (*plotting_function_t)(float);

void render(window_size_t w, render_state_t* state, plotting_function_t f,
            int delay);
void plot_axes(window_size_t w, render_state_t* state);
void plot_function(window_size_t w, render_state_t* state,
                   plotting_function_t f, int delay);