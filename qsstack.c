
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t l;
    size_t r;
} task_t;

typedef struct {
    task_t* _array;
    size_t _capacity;
    size_t size;
} stack_t;

stack_t* make_stack();
void push(stack_t* st, size_t l, size_t r);
task_t pop(stack_t* st);
task_t top(stack_t* st);
void cleanup(stack_t* st);

stack_t* make_stack() {
    stack_t* new = malloc(sizeof(stack_t));
    new->_capacity = 10;
    new->size = 0;
    new->_array = malloc(sizeof(task_t) * 10);
    return new;
}

void push(stack_t* st, size_t l, size_t r) {
    if (st->size == st->_capacity) {
        st->_array = realloc(st->_array, st->_capacity * 2 * sizeof(task_t));
        st->_capacity *= 2;
    }
    st->_array[st->size].l = l;
    st->_array[st->size].r = r;
    st->size++;
}

task_t pop(stack_t* st) {
    task_t val = top(st);
    st->size--;
    return val;
}

task_t top(stack_t* st) {
    return st->_array[st->size - 1];
}

void cleanup(stack_t* st) {
    free(st->_array);
    free(st);
}

void swap(int* arr, size_t i, size_t j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

size_t partition(int* arr, size_t l, size_t r) {
    int pivot = arr[r - 1];
    size_t i = l;
    for (size_t j = l; j < r - 1; ++j) {
        if (arr[j] < pivot) {
            swap(arr, i, j);
            ++i;
        }
    }
    swap(arr, i, r - 1);
    return i;
}

void quicksort(int* arr, size_t n) {
    stack_t* st = make_stack();
    push(st, 0, n);
    while (st->size) {
        size_t l = top(st).l;
        size_t r = pop(st).r;
        if (l + 1 >= r) {
            continue;
        }
        size_t m = partition(arr, l, r);
        push(st, l, m);
        push(st, m + 1, r);
    }
    cleanup(st);
}

int main() {
    size_t n;
    scanf("%zu", &n);
    int* arr = calloc(n, sizeof(int));
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    quicksort(arr, n);
    for (size_t i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}
