
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* _array;
    size_t _capacity;
    size_t size;
} stack_t;

stack_t* make_stack();
void push(stack_t* st, int val);
int pop(stack_t* st);
int top(stack_t* st);
void cleanup(stack_t* st);

stack_t* make_stack() {
    stack_t* new = malloc(sizeof(stack_t));
    new->_capacity = 10;
    new->size = 0;
    new->_array = malloc(sizeof(int) * 10);
    return new;
}

void push(stack_t* st, int val) {
    if (st->size == st->_capacity) {
        st->_array = realloc(st->_array, st->_capacity * 2 * sizeof(int));
        st->_capacity *= 2;
    }
    st->_array[st->size] = val;
    st->size++;
}

int pop(stack_t* st) {
    int val = top(st);
    st->size--;
    return val;
}

int top(stack_t* st) {
    return st->_array[st->size - 1];
}

void cleanup(stack_t* st) {
    free(st->_array);
    free(st);
}

void const_handler(stack_t* st) {
    int x;
    scanf("%d", &x);
    push(st, x);
}

void add_handler(stack_t* st) {
    int a = pop(st);
    int b = pop(st);
    push(st, a + b);
}

void sub_handler(stack_t* st) {
    int a = pop(st);
    int b = pop(st);
    push(st, a - b);
}

void mul_handler(stack_t* st) {
    int a = pop(st);
    int b = pop(st);
    push(st, a * b);
}

void div_handler(stack_t* st) {
    int a = pop(st);
    int b = pop(st);
    push(st, a / b);
}

void max_handler(stack_t* st) {
    int a = pop(st);
    int b = pop(st);
    push(st, a > b ? a : b);
}

void min_handler(stack_t* st) {
    int a = pop(st);
    int b = pop(st);
    push(st, a < b ? a : b);
}

void neg_handler(stack_t* st) {
    int a = pop(st);
    push(st, -a);
}

void dup_handler(stack_t* st) {
    push(st, top(st));
}

void swap_handler(stack_t* st) {
    int a = pop(st);
    int b = pop(st);
    push(st, a);
    push(st, b);
}
int main() {
    int n;
    scanf("%d", &n);
    stack_t* st = make_stack();
    for (int i = 0; i < n; ++i) {
        char* command;
        scanf("%ms", &command);
        if (!strcmp(command, "CONST")) {
            const_handler(st);
        } else if (!strcmp(command, "ADD")) {
            add_handler(st);
        } else if (!strcmp(command, "SUB")) {
            sub_handler(st);
        } else if (!strcmp(command, "MUL")) {
            mul_handler(st);
        } else if (!strcmp(command, "DIV")) {
            div_handler(st);
        } else if (!strcmp(command, "MAX")) {
            max_handler(st);
        } else if (!strcmp(command, "MIN")) {
            min_handler(st);
        } else if (!strcmp(command, "NEG")) {
            neg_handler(st);
        } else if (!strcmp(command, "DUP")) {
            dup_handler(st);
        } else if (!strcmp(command, "SWAP")) {
            swap_handler(st);
        }
        free(command);
    }
    printf("%d\n", top(st));
    cleanup(st);
    return 0;
}

