#include "ast.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

double ast_evaluate(ast_node_t* node, double x_value) {
    if (node == NULL) {
        return 0;
    }

    switch (node->type) {
        case AST_NODE_VARIABLE:
            if (strcmp(node->varname, "pi") == 0) {
                return M_PI;
            } else if (strcmp(node->varname, "e") == 0) {
                return M_E;
            }

            return x_value;

        case AST_NODE_CONSTANT:
            return node->constant;

        case AST_NODE_OPERATOR:
            switch (node->op) {
                case AST_OPERATOR_ADD:
                    return ast_evaluate(node->left, x_value) +
                           ast_evaluate(node->right, x_value);
                case AST_OPERATOR_SUBTRACT:
                    return ast_evaluate(node->left, x_value) -
                           ast_evaluate(node->right, x_value);
                case AST_OPERATOR_MULTIPLY:
                    return ast_evaluate(node->left, x_value) *
                           ast_evaluate(node->right, x_value);
                case AST_OPERATOR_DIVIDE:
                    return ast_evaluate(node->left, x_value) /
                           ast_evaluate(node->right, x_value);
                case AST_OPERATOR_POWER:
                    return pow(ast_evaluate(node->left, x_value),
                               ast_evaluate(node->right, x_value));
                default:
                    return 0;
            }

        case AST_NODE_FUNCTION:
            switch (node->func) {
                case AST_FUNCTION_SIN:
                    return sin(ast_evaluate(node->left, x_value));
                case AST_FUNCTION_COS:
                    return cos(ast_evaluate(node->left, x_value));
                default:
                    return 0;
            }

        default:
            return 0;
    }

    return 0;
}
