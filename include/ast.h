#pragma once

#define NODE_LIST    \
    X(NODE_CONSTANT) \
    X(NODE_OPERATOR) \
    X(NODE_FUNCTION) \
    X(NODE_VARIABLE) \
    X(NODE__COUNT)

#define OPERATOR_LIST    \
    X(OPERATOR_ADD)      \
    X(OPERATOR_SUBTRACT) \
    X(OPERATOR_MULTIPLY) \
    X(OPERATOR_DIVIDE)   \
    X(OPERATOR_POWER)    \
    X(OPERATOR__COUNT)

#define FUNCTION_LIST \
    X(FUNCTION_SIN)   \
    X(FUNCTION_COS)   \
    X(FUNCTION__COUNT)

#define X(name) name,
typedef enum { NODE_LIST } ast_node_e;
typedef enum { OPERATOR_LIST } ast_operator_e;
typedef enum { FUNCTION_LIST } ast_function_e;
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
        NODE_LIST
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
        OPERATOR_LIST
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
        FUNCTION_LIST
#undef X
        default:
            return "invalid function type";
    }
}