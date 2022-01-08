
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int k;
    int v;
    size_t index;
} node_t;

#define swap(a, b)                                                             \
  {                                                                            \
    node_t *temp = a;                                                          \
    a = b;                                                                     \
    b = temp;                                                                  \
  }

typedef struct {
    node_t** _array;
    size_t _capacity;
    size_t size;
} queue_t;

queue_t* queue_make(size_t sz);
int queue_max(queue_t* q);
char queue_empty(queue_t* q);
void* queue_push(queue_t* q, int k, int v);
void* queue_pop(queue_t* q);
void queue_inc_key(queue_t* q, node_t* ptr, int k);
void queue_cleanup(queue_t* q);

queue_t* queue_make(size_t sz) {
    queue_t* new = malloc(sizeof(queue_t));
    new->_capacity = sz;
    new->size = 0;
    new->_array = calloc(sz, sizeof(node_t*));
    return new;
}

int queue_max(queue_t* q) {
    return q->_array[0]->v;
}

char queue_empty(queue_t* q) {
    return q->size == 0 ? 1 : 0;
}

void* queue_push(queue_t* q, int k, int v) {
    size_t i = q->size;
    q->size++;
    node_t* new = malloc(sizeof(node_t));
    q->_array[i] = new;
    new->index = i;
    new->k = k;
    new->v = v;
    while (i > 0 && q->_array[(i - 1) / 2]->k < k) {
        swap(q->_array[(i - 1) / 2], q->_array[i]);
        q->_array[i]->index = i;
        i = (i - 1) / 2;
    }
    q->_array[i]->index = i;
    return new;
}

void* queue_pop(queue_t* q) {
    node_t* ret = q->_array[0];
    q->size--;
    if (q->size > 0) {
        q->_array[0] = q->_array[q->size];
        q->_array[0]->index = 0;
        size_t i = 0;
        while (1) {
            size_t l = i * 2 + 1;
            size_t r = i * 2 + 2;
            size_t top = i;
            if (l < q->size && q->_array[l]->k > q->_array[i]->k) {
                i = l;
            }
            if (r < q->size && q->_array[r]->k > q->_array[i]->k) {
                i = r;
            }
            if (i == top) {
                break;
            }
            swap(q->_array[i], q->_array[top]);
            q->_array[i]->index = i;
            q->_array[top]->index = top;
        }
    }
    return ret;
}

void queue_inc_key(queue_t* q, node_t* ptr, int k) {
    size_t i = ptr->index;
    ptr->k = k;
    while (i > 0 && q->_array[(i - 1) / 2]->k < k) {
        swap(q->_array[(i - 1) / 2], q->_array[i]);
        q->_array[i]->index = i;
        i = (i - 1) / 2;
    }
    ptr->index = i;
}

void queue_cleanup(queue_t* q) {
    for (size_t i = 0; i < q->size; ++i) {
        free(q->_array[i]);
    }
    free(q->_array);
    free(q);
}

int main() {
    int k;
    scanf("%d", &k);
    size_t sz = 0;
    int sizes[k];
    int* arrays[k];
    for (int i = 0; i < k; ++i) {
        scanf("%d", &sizes[i]);
        arrays[i] = malloc(sizes[i] * sizeof(int));
        sz += (size_t)sizes[i];
    }
    queue_t* q = queue_make(sz);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < sizes[i]; ++j) {
            scanf("%d", &arrays[i][j]);
        }
    }
    int indexes[k];
    for (int i = 0; i < k; ++i) {
        queue_push(q, -arrays[i][0], i);
        indexes[i] = 1;
    }
    for (size_t i = 0; i < sz; ++i) {
        node_t* v = queue_pop(q);
        printf("%d ", -v->k);
        int array_index = v->v;
        if (indexes[array_index] < sizes[array_index]) {
            queue_push(q, -arrays[array_index][indexes[array_index]], array_index);
            indexes[array_index]++;
        }
        free(v);
    }
    printf("\n");
    queue_cleanup(q);
    for (int i = 0; i < k; ++i) {
        free(arrays[i]);
    }
    return 0;
}
