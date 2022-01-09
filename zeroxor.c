
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int k;
    size_t v;
} node_t;

typedef struct {
    node_t* array;
    size_t top;
    size_t capacity;
} list_t;

node_t* list_search(list_t* list, int k);
void list_push_back(list_t* list, int k, size_t v);

node_t* list_search(list_t* list, int k) {
    for (size_t i = 0; i < list->top; ++i) {
        if (list->array[i].k == k) {
            return &list->array[i];
        }
    }
    return NULL;
}

void list_push_back(list_t* list, int k, size_t v) {
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

#define hash(i, m) (abs(i) % m)

disparray_t* disparray_make(size_t m);
void disparray_cleanup(disparray_t* t);
long disparray_get(disparray_t* t, int i);
void disparray_insert(disparray_t* t, int i, size_t v);

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

long disparray_get(disparray_t* t, int i) {
    node_t* v = list_search(&t->table[hash(i, (int)t->m)], i);
    if (v) {
        return (long)v->v;
    }
    return -1;
}

void disparray_insert(disparray_t* t, int i, size_t v) {
    list_t* list = &t->table[hash(i, (int)t->m)];
    node_t* node = list_search(list, i);
    if (!node) {
        list_push_back(list, i, v);
    } else {
        node->v = v;
    }
}

#define DISPARRAY_SZ 100000

int main() {
    size_t n;
    scanf("%zu", &n);
    disparray_t* disparray = disparray_make(DISPARRAY_SZ);
    int xor = 0;
    int count[n];
    memset(count, 0, sizeof(int) * n);
    long long ans = 0;
    int num;
    scanf("%d", &num);
    xor ^= num;
    if (!num) {
        count[0] = 1;
        ans++;
    }
    disparray_insert(disparray, xor, 0);
    for (size_t i = 1; i < n; ++i) {
        scanf("%d", &num);
        xor ^= num;
        long ind = disparray_get(disparray, xor);
        if (ind != -1) {
            count[i] = count[ind] + 1;
        }
        disparray_insert(disparray, xor, i);
        ans += count[i];
    }
    printf("%lld\n", ans);
    disparray_cleanup(disparray);
    return 0;
}
