#pragma once

#include "screen.h"

#define DEFAULT_X_OFFSET 0
#define DEFAULT_Y_OFFSET 0
#define DEFAULT_X_STEP 0.05
#define DEFAULT_Y_STEP 0.5

typedef struct {
    double x_offset, y_offset;
    double x_step, y_step;
} render_state_t;

typedef double (*plotting_function_t)(double);

void render(window_size_t w, render_state_t* state, plotting_function_t f,
            int delay);
void plot_axes(window_size_t w, render_state_t* state);
void plot_function(window_size_t w, render_state_t* state,
                   plotting_function_t f, int delay);