#include "stack.h"
#include "status_stack.h"
#include <stdio.h>
#include <stdlib.h>

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
                              " be a null pointer!\n");
    return res;
}

int push(Stack* stack, void* value) {
    int res = SUCCESS;

    if(stack == 0) {
        res = EINVARG;
        goto out;
    }

    StackNode* new_node = malloc(sizeof(StackNode));
    new_node->value = value;

    if(new_node == 0) {
        res = EMEM;
        goto out;
    }

    if(stack->top != 0) {
        new_node->next = stack->top;
    } else {
        new_node->next = 0;
    }

    stack->top = new_node;
    stack->size += 1; 

out:
    if(res == EINVARG) printf("EINVARG: the `stack` argument must not"
                              " be a null pointer!\n");
    if(res == EMEM) printf("EMEM: failed to allocate memory to"
            " `new_node`!\n");
    return res;
}

static int delete_top_node(Stack* stack) {
    int res = SUCCESS;
    if(stack == 0) {
        res = EINVARG;
        goto out;
    }

    StackNode* cur_top = stack->top;
    if(cur_top == 0) {
        res = EUNFLOW;
        goto out;  
    }
    
    stack->top = cur_top->next;
    free(cur_top);
    stack->size -= 1;

out:
    if(res == EINVARG) printf("EINVARG: the `stack` argument must not"
                              " be a null pointer!\n");
    if(res == EUNFLOW) printf("EUNFLOW: stack underflow! The stack is"
                              " empty; there are no elements to"
                              " delete. \n");
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

    *top_value_ref = stack->top->value; 
    delete_top_node(stack);

out:
    if(res == EINVARG) printf("EINVARG: neither the `stack` nor the"
                              " `top_value_ref` argument can be a null"
                              " pointer!\n");
    if(res == EUNFLOW) printf("EUNFLOW: stack underflow! The stack is"
                              " empty; there are no elements to"
                              " pop.\n");
    return res;
}

int delete_stack(Stack** stack_ref) {
    int res = SUCCESS;

    if(stack_ref == 0) {
        res = EINVARG;
        goto out;
    }

    Stack* stack = *stack_ref;

    if(stack == 0) {
        res = EINVARG;
        goto out;
    }

    while(stack->top != 0) {
        delete_top_node(stack);
    }

    free(stack);

out:
    if(res == EINVARG) printf("EINVARG: the `stack_ref` argument must"
                              " not be a null pointer, and must point"
                              " to a stack!");
    return res;
}

int size(Stack* stack) {
    int status = 0;

    if(stack == 0) {
        status = EINVARG;
        goto out;
    }

out:
    if(status == EINVARG) {
        printf("EINVARG: the `stack` argument must not"
               " be a null pointer!\n");
        return status;
    } else {
        return stack->size;
    }
}

