#ifndef STACK_H
#define STACK_H

typedef struct stack_node {
    void* value;
    struct stack_node* next;
} StackNode;


typedef struct {
    StackNode* top;
    int size;
} Stack;

void init_stack(Stack* stack);
int push(Stack* stack, void* value);
int pop(Stack* stack, void** top_value);
int size(Stack* stack);
int delete_stack(Stack** stack_ref);

#endif
