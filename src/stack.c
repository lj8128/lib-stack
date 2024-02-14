#include "stack.h"
#include "status_stack.h"
#include <stdio.h>

int init_stack(Stack* stack) {
    int res = SUCCESS;
    
    if(stack == 0) {
        res = EINVARG;
        goto out;
    }

    stack->top = 0;
    stack->size = 0;

out:
    if(res == EINVARG) printf("EINVARG: the `stack` argument must not"
                              " be a null pointer!");
    return res;
}

int push(Stack* stack, void* value) {
    int res = SUCCESS;

    if(stack == 0 || value == 0) {
        res = EINVARG;
        goto out;
    }

    StackNode* newNode = malloc(sizeof(StackNode));
    newNode->value = value;

    if(newNode == 0) {
        res = EMEM;
        goto out;
    }

    if(stack->top != 0) {
        newNode->next = stack->top;
    } else {
        newNode->next = 0;
    }

    stack->top = newNode;
    stack->size += 1; 

out:
    if(res == EINVARG) printf("EINVARG: neither the `stack` nor the"
                              " `value` argument can be a null"
                              " pointer!");
    if(res == EMEM) printf("EMEM: failed to allocate memory for"
            " `newNode`!");
    return res;
}

int pop(Stack* stack, void** top_value_ref) {
    int res = SUCCESS;

    if(stack == 0 || top_value_ref == 0) {
        res = EINVARG;
        goto out;
    }

    if(stack->top == 0) {
        res = EUNFLOW;
        goto out;
    }

    StackNode* cur_top = stack->top; 
    *top_value_ref = cur_top->value; 
    stack->top = cur_top->next;
  
    free(cur_top);

    stack->size -= 1;

out:
    if(res == EINVARG) printf("EINVARG: neither the `stack` nor the"
                              " `top_value_ref` argument can be a null"
                              " pointer!");
    if(res == EUNFLOW) printf("EUNFLOW: stack underflow; the stack is"
                              " empty!");
    return res;
}

int size(Stack* stack) {
    return stack->size;
}

int delete_stack(Stack** stack_ref) {
    int res = SUCCESS;

    if(stack_ref == 0) {
        res = EINVARG;
        goto out;
    }

    Stack* stack = *stack_ref;
    void** top_val_ref;

    while(stack->top != 0) {
       pop(stack, top_val_ref); 
    }

    free(stack);

out:
    if(res == EINVARG) printf("EINVARG: the `stack_ref` argument must"
                              " not be a null pointer!");
    return res;
}

