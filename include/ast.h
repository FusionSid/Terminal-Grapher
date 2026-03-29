#pragma once

#define AST_NODE_LIST    \
    X(AST_NODE_CONSTANT) \
    X(AST_NODE_OPERATOR) \
    X(AST_NODE_FUNCTION) \
    X(AST_NODE_VARIABLE) \
    X(AST_NODE__COUNT)

#define AST_OPERATOR_LIST    \
    X(AST_OPERATOR_ADD)      \
    X(AST_OPERATOR_SUBTRACT) \
    X(AST_OPERATOR_MULTIPLY) \
    X(AST_OPERATOR_DIVIDE)   \
    X(AST_OPERATOR_POWER)    \
    X(AST_OPERATOR__COUNT)

#define AST_FUNCTION_LIST \
    X(AST_FUNCTION_SIN)   \
    X(AST_FUNCTION_COS)   \
    X(AST_FUNCTION__COUNT)

#define X(name) name,
typedef enum { AST_NODE_LIST } ast_node_e;
typedef enum { AST_OPERATOR_LIST } ast_operator_e;
typedef enum { AST_FUNCTION_LIST } ast_function_e;
#undef X

typedef struct ast_node_t ast_node_t;

struct ast_node_t {
    ast_node_e type;
    union {
        char* varname;
        double constant;
        ast_operator_e op;
        ast_function_e func;
    };
    struct ast_node_t* left;
    struct ast_node_t* right;
};

double ast_evaluate(ast_node_t* node, double x_value);

static inline const char* node_to_string(ast_node_e node) {
    switch (node) {
#define X(name) \
    case name:  \
        return #name;
        AST_NODE_LIST
#undef X
        default:
            return "invalid node type";
    }
}

static inline const char* operator_to_string(ast_operator_e op) {
    switch (op) {
#define X(name) \
    case name:  \
        return #name;
        AST_OPERATOR_LIST
#undef X
        default:
            return "invalid operator type";
    }
}

static inline const char* function_to_string(ast_function_e func) {
    switch (func) {
#define X(name) \
    case name:  \
        return #name;
        AST_FUNCTION_LIST
#undef X
        default:
            return "invalid function type";
    }
}