#pragma once

#include "screen.h"

#define DEFAULT_X_OFFSET 0
#define DEFAULT_Y_OFFSET 0
#define DEFAULT_X_STEP 0.05
#define DEFAULT_Y_STEP 0.5

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