
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 2000000001

int max(int a, int b) {
    return a > b ? a : b;
}

typedef struct {
    int* _array;
    int* _max;
    size_t _capacity;
    size_t _top1;
    size_t _top2;
} dstack_t;

dstack_t* dstack_make(size_t sz);
char dstack_empty1(dstack_t* st);
char dstack_empty2(dstack_t* st);
void dstack_push1(dstack_t* st, int v);
void dstack_push2(dstack_t* st, int v);
int dstack_pop1(dstack_t* st);
int dstack_pop2(dstack_t* st);
int dstack_top1(dstack_t* st);
int dstack_top2(dstack_t* st);
int dstack_max1(dstack_t* st);
int dstack_max2(dstack_t* st);
void dstack_cleanup(dstack_t* st);

dstack_t* dstack_make(size_t sz) {
    dstack_t* new = malloc(sizeof(dstack_t));
    new->_array = malloc(sz * sizeof(int));
    new->_max = malloc(sz * sizeof(int));
    new->_capacity = sz;
    new->_top1 = 0;
    new->_top2 = sz - 1;
    return new;
}

char dstack_empty1(dstack_t* st) {
    return st->_top1 == 0 ? 1 : 0;
}

char dstack_empty2(dstack_t* st) {
    return st->_top2 == st->_capacity - 1 ? 1 : 0;
}

void dstack_push1(dstack_t* st, int v) {
    if (st->_top1) {
        st->_max[st->_top1] = max(st->_max[st->_top1 - 1], v);
    } else {
        st->_max[st->_top1] = v;
    }
    st->_array[st->_top1] = v;
    st->_top1++;
}

void dstack_push2(dstack_t* st, int v) {
    if (st->_top2 != st->_capacity - 1) {
        st->_max[st->_top2] = max(st->_max[st->_top2 + 1], v);
    } else {
        st->_max[st->_top2] = v;
    }
    st->_array[st->_top2] = v;
    st->_top2--;
}

int dstack_pop1(dstack_t* st) {
    st->_top1--;
    return st->_array[st->_top1];
}

int dstack_pop2(dstack_t* st) {
    return st->_array[++st->_top2];
}

int dstack_top1(dstack_t* st) {
    return st->_array[st->_top1 - 1];
}

int dstack_top2(dstack_t* st) {
    return st->_array[st->_top2 + 1];
}

int dstack_max1(dstack_t* st) {
    return st->_top1 == 0 ? -INF : st->_max[st->_top1 - 1];
}

int dstack_max2(dstack_t* st) {
    return st->_top2 == st->_capacity - 1 ? -INF : st->_max[st->_top2 + 1];
}

void dstack_cleanup(dstack_t* st) {
    free(st->_array);
    free(st->_max);
    free(st);
}

typedef dstack_t queue_t;

queue_t* queue_make(size_t sz);
char queue_empty(queue_t* q);
void queue_push(queue_t* q, int v);
int queue_pop(queue_t* q);
int queue_front(queue_t* q);
int queue_max(queue_t* q);
void queue_cleanup(queue_t* q);

queue_t* queue_make(size_t sz) {
    return dstack_make(sz);
}

char queue_empty(queue_t* q) {
    return dstack_empty1(q) && dstack_empty2(q);
}

void queue_push(queue_t* q, int v) {
    dstack_push1(q, v);
}

int queue_pop(queue_t* q) {
    if (dstack_empty2(q)) {
        while (!dstack_empty1(q)) {
            dstack_push2(q, dstack_pop1(q));
        }
    }
    return dstack_pop2(q);
}

int queue_front(queue_t* q) {
    if (dstack_empty2(q)) {
        while (!dstack_empty1(q)) {
            dstack_push2(q, dstack_pop1(q));
        }
    }
    return dstack_top2(q);
}

int queue_max(queue_t* q) {
    return max(dstack_max1(q), dstack_max2(q));
}

void queue_cleanup(queue_t* q) {
    dstack_cleanup(q);
}

int main() {
    int n;
    scanf("%d", &n);
    queue_t* q = queue_make(n);
    for (int i = 0; i < n; ++i) {
        char* command;
        scanf("%ms", &command);
        if (!strcmp(command, "ENQ")) {
            int x;
            scanf("%d", &x);
            queue_push(q, x);
        } else if (!strcmp(command, "DEQ")) {
            printf("%d\n", queue_pop(q));
        } else if (!strcmp(command, "MAX")) {
            printf("%d\n", queue_max(q));
        } else if (!strcmp(command, "EMPTY")) {
            if (queue_empty(q)) {
                printf("true\n");
            } else {
                printf("false\n");
            }
        }
        free(command);
    }
    queue_cleanup(q);
    return 0;
}
