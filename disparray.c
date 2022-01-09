
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t k;
    int v;
} node_t;

typedef struct {
    node_t* array;
    size_t top;
    size_t capacity;
} list_t;

node_t* list_search(list_t* list, size_t k);
void list_push_back(list_t* list, size_t k, int v);

node_t* list_search(list_t* list, size_t k) {
    for (size_t i = 0; i < list->top; ++i) {
        if (list->array[i].k == k) {
            return &list->array[i];
        }
    }
    return NULL;
}

void list_push_back(list_t* list, size_t k, int v) {
    if (list->capacity == list->top) {
        list->array = realloc(list->array, list->capacity * 3 * sizeof(node_t));
        list->capacity *= 3;
    }
    list->array[list->top].k = k;
    list->array[list->top].v = v;
    list->top++;
}

typedef struct {
    list_t* table;
    size_t m;
} disparray_t;

#define hash(i, m) (i % m)

disparray_t* disparray_make(size_t m);
void disparray_cleanup(disparray_t* t);
int disparray_get(disparray_t* t, size_t i);
void disparray_insert(disparray_t* t, size_t i, int v);

disparray_t* disparray_make(size_t m) {
    disparray_t* new = malloc(sizeof(disparray_t));
    new->table = malloc(m * sizeof(list_t));
    new->m = m;
    for (size_t i = 0; i < m; ++i) {
        new->table[i].array = malloc(10 * sizeof(node_t));
        new->table[i].capacity = 10;
        new->table[i].top = 0;
    }
    return new;
}

void disparray_cleanup(disparray_t* t) {
    for (size_t i = 0; i < t->m; ++i) {
        free(t->table[i].array);
    }
    free(t->table);
    free(t);
}

int disparray_get(disparray_t* t, size_t i) {
    node_t* v = list_search(&t->table[hash(i, t->m)], i);
    if (v) {
        return v->v;
    }
    return 0;
}

void disparray_insert(disparray_t* t, size_t i, int v) {
    list_t* list = &t->table[hash(i, t->m)];
    node_t* node = list_search(list, i);
    if (!node) {
        list_push_back(list, i, v);
    } else {
        node->v = v;
    }
}

int main() {
    size_t n;
    size_t m;
    scanf("%zu%zu", &n, &m);
    disparray_t* disparray = disparray_make(m);
    for (size_t i = 0; i < n; ++i) {
        char* op;
        scanf("%ms", &op);
        if (!strcmp(op, "ASSIGN")) {
            size_t index;
            int value;
            scanf("%zu%d", &index, &value);
            disparray_insert(disparray, index, value);
        } else if (!strcmp(op, "AT")) {
            size_t index;
            scanf("%zu", &index);
            printf("%d\n", disparray_get(disparray, index));
        }
        free(op);
    }
    disparray_cleanup(disparray);
    return 0;
}
