#include "stack.h"
#include "status_stack.h"
#include "test_setup_and_cleanup.h"
#include "test_execution.h"
#include "status_tests_and_routines.h"
#include <stdlib.h>

Stack* test_stack;
typedef struct {
    double x;
    double y;
} Point;

static RoutineResult before_each() {
    test_stack = malloc(sizeof(Stack));
    return init_stack(test_stack) == SUCCESS ?
           ROUTINE_SUCCEEDED : ROUTINE_FAILED;
}

static RoutineResult after_each() {
    return delete_stack(&test_stack) == SUCCESS ?
           ROUTINE_SUCCEEDED : ROUTINE_FAILED;
}

static TestResult test_push() {
    TestResult res = TEST_PASSED;
    Point* p_A = malloc(sizeof(Point));
    *p_A = (Point){ .x = 1, .y = 2 }; 
    push(test_stack, (void*)p_A);

    if(test_stack->top->value != (void*)p_A) {
        print_freq("The value of the top node of the stack should be"
                " p_A!");
        res = TEST_FAILED;
        goto out;
    }

    Point* p_B = malloc(sizeof(Point));
    *p_B = (Point){ .x = 3, .y = 4 }; 
    push(test_stack, (void*)p_B);

    if(test_stack->top->value != (void*)p_B) {
        print_freq("The value of the top node of the stack should be"
                " p_B!");
        res = TEST_FAILED;
        goto out;
    }

out:
    free(p_A);
    free(p_B);
    return res; 
}

static TestResult test_pop() {
    TestResult res = TEST_PASSED;

    Point* p_A = malloc(sizeof(Point));
    *p_A = (Point){ .x = 1, .y = 2 }; 
    Point* p_B = malloc(sizeof(Point));
    *p_B = (Point){ .x = 1, .y = 2 }; 
    Point* p_C = malloc(sizeof(Point));
    *p_C = (Point){ .x = 1, .y = 2 }; 

    push(test_stack, (void*)p_A);
    push(test_stack, (void*)p_B);
    push(test_stack, (void*)p_C);

    void** cur_top_val_ref = malloc(sizeof(Point*));
    pop(test_stack, cur_top_val_ref);
    if(*cur_top_val_ref != (void*)p_C) {
        print_freq("(void*)p_C should have been popped!"); 
        res = TEST_FAILED;
        goto out;
    }

    pop(test_stack, cur_top_val_ref);
    if(*cur_top_val_ref != (void*)p_B) {
        print_freq("(void*)p_B should have been popped!"); 
        res = TEST_FAILED;
        goto out;
    }

    pop(test_stack, cur_top_val_ref);
    if(*cur_top_val_ref != (void*)p_A) {
        print_freq("(void*)p_A should have been popped!"); 
        res = TEST_FAILED;
        goto out;
    }

    if(pop(test_stack, cur_top_val_ref) != EUNFLOW) {
        print_freq("The stack should catch underflows!");
        res = TEST_FAILED;
        goto out;
    }

out:
    free(p_A);
    free(p_B);
    free(p_C);
    free(cur_top_val_ref);
    return res;
}

static TestResult test_peek() {
    TestResult res = TEST_PASSED;

    Point* p_A = malloc(sizeof(Point));
    *p_A = (Point){ .x = 1, .y = 2 }; 
    Point* p_B = malloc(sizeof(Point));
    *p_B = (Point){ .x = 1, .y = 2 }; 
    Point* p_C = malloc(sizeof(Point));
    *p_C = (Point){ .x = 1, .y = 2 }; 

    push(test_stack, (void*)p_A);
    push(test_stack, (void*)p_B);
    push(test_stack, (void*)p_C);

    void** cur_top_val_ref = malloc(sizeof(Point*));
    peek(test_stack, cur_top_val_ref);
    if(*cur_top_val_ref != (void*)p_C) {
        print_freq("(void*)p_C should have been peeked at!"); 
        res = TEST_FAILED;
        goto out;
    }

    pop(test_stack, cur_top_val_ref);
    peek(test_stack, cur_top_val_ref);
    if(*cur_top_val_ref != (void*)p_B) {
        print_freq("(void*)p_B should have been peeked at!"); 
        res = TEST_FAILED;
        goto out;
    }

    pop(test_stack, cur_top_val_ref);
    peek(test_stack, cur_top_val_ref);
    if(*cur_top_val_ref != (void*)p_A) {
        print_freq("(void*)p_A should have been peeked at!"); 
        res = TEST_FAILED;
        goto out;
    }

    pop(test_stack, cur_top_val_ref);
    if(peek(test_stack, cur_top_val_ref) != ESTACKEMPTY) {
        print_freq("The stack should catch peeking at an empty"
                   " stack!");
        res = TEST_FAILED;
        goto out;
    }

out:
    free(p_A);
    free(p_B);
    free(p_C);
    free(cur_top_val_ref);
    return res;
}

static TestResult test_size() {
    TestResult res = TEST_PASSED;
    
    if(size(test_stack) != 0) {
        print_freq("A stack that was just initialized should be"
                   " empty!");
        res = TEST_FAILED;
        goto out;
    }

    Point* p_A = malloc(sizeof(Point));
    *p_A = (Point){ .x = 1, .y = 2 }; 
    push(test_stack, (void*)p_A);

    Point* p_B = malloc(sizeof(Point));
    *p_B = (Point){ .x = 2, .y = 3 }; 
    push(test_stack, (void*)p_B);

    if(size(test_stack) != 2) {
        print_freq("The stack's size should be 2!");
        res = TEST_FAILED;
        goto out;
    }

    void** cur_top_val_ref = malloc(sizeof(Point*));
    pop(test_stack, cur_top_val_ref);

    if(size(test_stack) != 1) {
        print_freq("The stack's size should be 1!");
        res = TEST_FAILED;
        goto out;
    }

out:
    free(p_A);
    free(p_B);
    free(cur_top_val_ref);
    return res;
}

int main() {
    int res = SUCCESS;

    TestCatalog* catalog = malloc(sizeof(TestCatalog));
    init_test_catalog(catalog);

    register_test(catalog, "test_push", test_push); 
    register_test(catalog, "test_pop", test_pop); 
    register_test(catalog, "test_peek", test_peek); 
    register_test(catalog, "test_size", test_size); 

    register_before_each_routine(catalog, before_each);
    register_after_each_routine(catalog, after_each);

    run_all_tests(catalog);
    delete_test_catalog(&catalog);

    return res;
}

