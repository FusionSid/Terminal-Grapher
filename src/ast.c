#include "ast.h"

#include <stdlib.h>

#include "math.h"

double ast_evaluate(ast_node_t* node, double x_value) {
    if (node == NULL) {
        return 0;
    }

    switch (node->type) {
        case NODE_VARIABLE:
            return x_value;

        case NODE_CONSTANT:
            return node->constant;

        case NODE_OPERATOR:
            switch (node->op) {
                case OPERATOR_ADD:
                    return ast_evaluate(node->left, x_value) +
                           ast_evaluate(node->right, x_value);
                case OPERATOR_SUBTRACT:
                    return ast_evaluate(node->left, x_value) -
                           ast_evaluate(node->right, x_value);
                case OPERATOR_MULTIPLY:
                    return ast_evaluate(node->left, x_value) *
                           ast_evaluate(node->right, x_value);
                case OPERATOR_DIVIDE:
                    return ast_evaluate(node->left, x_value) /
                           ast_evaluate(node->right, x_value);
                case OPERATOR_POWER:
                    return pow(ast_evaluate(node->left, x_value),
                               ast_evaluate(node->right, x_value));
                default:
                    return 0;
            }

        case NODE_FUNCTION:
            switch (node->func) {
                case FUNCTION_SIN:
                    return sin(ast_evaluate(node->left, x_value));
                case FUNCTION_COS:
                    return cos(ast_evaluate(node->left, x_value));
                default:
                    return 0;
            }

        default:
            return 0;
    }

    return 0;
}
