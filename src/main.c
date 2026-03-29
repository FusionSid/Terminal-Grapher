#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "ast.h"
#include "codes.h"
#include "input.h"
#include "render.h"
#include "screen.h"
#include "term.h"

int main() {
    // ast bellow is: y= 10 * sin(x - 2) * cos(2 * x)
    // ast_node_t ast = {
    //     .type = AST_NODE_OPERATOR,
    //     .op = AST_OPERATOR_MULTIPLY,
    //     .left = &(ast_node_t){.type = AST_NODE_OPERATOR,
    //                           .op = AST_OPERATOR_MULTIPLY,
    //                           .left = &(ast_node_t){.type = AST_NODE_CONSTANT,
    //                                                 .constant = 10.0},
    //                           .right =
    //                               &(ast_node_t){
    //                                   .type = AST_NODE_FUNCTION,
    //                                   .func = AST_FUNCTION_SIN,
    //                                   .left = &(ast_node_t){.type =
    //                                                             AST_NODE_OPERATOR,
    //                                                         .op =
    //                                                         AST_OPERATOR_SUBTRACT,
    //                                                         .left =
    //                                                         &(ast_node_t){.type
    //                                                         = AST_NODE_VARIABLE},
    //                                                         .right =
    //                                                         &(ast_node_t){.type
    //                                                         =
    //                                                                                    AST_NODE_CONSTANT,
    //                                                                                .constant = 2.0}}}},
    //     .right = &(ast_node_t){
    //         .type = AST_NODE_FUNCTION,
    //         .func = AST_FUNCTION_COS,
    //         .left = &(ast_node_t){
    //             .type = AST_NODE_OPERATOR,
    //             .op = AST_OPERATOR_MULTIPLY,
    //             .left = &(ast_node_t){.type = AST_NODE_CONSTANT, .constant
    //             = 2.0}, .right = &(ast_node_t){.type = AST_NODE_VARIABLE}}}};

    // y = 5
    // ast_node_t ast = {
    //     .type=AST_NODE_CONSTANT,
    //     .constant=5
    // };

    // y= x^5
    // ast_node_t ast =
    // {.type = AST_NODE_OPERATOR,
    //  .op = AST_OPERATOR_POWER,
    //  .left = &(ast_node_t){.type = AST_NODE_VARIABLE},
    //  .right = &(ast_node_t){.type = AST_NODE_CONSTANT, .constant = 5} };

    // y = e^x
    // ast_node_t ast = {
    //     .type = AST_NODE_OPERATOR,
    //     .op = AST_OPERATOR_POWER,
    //     .left = &(ast_node_t){.type = AST_NODE_VARIABLE, .varname = "e"},
    //     .right = &(ast_node_t){.type = AST_NODE_VARIABLE, .varname = "x"},
    // };

    ast_node_t ast = {
        .type = AST_NODE_OPERATOR,
        .op = AST_OPERATOR_ADD,
        .left =
            &(ast_node_t){
                .type = AST_NODE_OPERATOR,
                .op = AST_OPERATOR_POWER,
                .left = &(ast_node_t){.type = AST_NODE_VARIABLE, .varname = "e"},
                .right = &(ast_node_t){.type = AST_NODE_VARIABLE, .varname = "x"},
            },
        .right =
            &(ast_node_t){
                .type = AST_NODE_FUNCTION,
                .func=AST_FUNCTION_SIN,
                .left = &(ast_node_t){.type = AST_NODE_VARIABLE, .varname = "x"},
            },
    };

    init();
    enable_raw_mode();

    window_size_t w;
    get_window_size(&w);

    render_state_t render_state = {
        .x_offset = DEFAULT_X_OFFSET,
        .y_offset = DEFAULT_Y_OFFSET,
        .x_step = DEFAULT_X_STEP,
        .y_step = DEFAULT_Y_STEP,
    };
    render(w, &render_state, &ast,
           5000);  // initaly use non zero delay to animate drawing the function

    char c;
    while (1) {
        if (read(STDIN_FILENO, &c, 1) != 1) continue;

        if (c == 'q') break;

        if (apply_action(&render_state, c)) {
            render(w, &render_state, &ast, 0);
        }
    }

    deinit();
    return 0;
}
