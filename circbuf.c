
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* _array;
    size_t _capacity;
    size_t size;
    size_t _head;
    size_t _tail;
} queue_t;

queue_t* make_queue();
void push(queue_t* q, int v);
int pop(queue_t* q);
int front(queue_t* q);
char empty(queue_t* q);
void cleanup(queue_t* q);

queue_t* make_queue() {
    queue_t* new = malloc(sizeof(queue_t));
    new->_array = malloc(4 * sizeof(int));
    new->_capacity = 4;
    new->size = 0;
    new->_head = 0;
    new->_tail = 0;
    return new;
}

void push(queue_t* q, int v) {
    if (q->size == q->_capacity) {
        int* new = malloc(q->_capacity * 2 * sizeof(int));
        size_t i = q->_head;
        size_t new_i = 0;
        while (i != q->_tail) {
            new[new_i] = q->_array[i];
            new_i++;
            i++;
            if (i == q->_capacity) {
                i = 0;
            }
        }
        new[new_i] = q->_array[i];
        free(q->_array);
        q->_array = new;
        q->_capacity *= 2;
        q->_head = 0;
        q->_tail = new_i;
    }
    if (q->size) {
        q->_tail++;
        if (q->_tail == q->_capacity) {
            q->_tail = 0;
        }
    }
    q->_array[q->_tail] = v;
    q->size++;
}

int pop(queue_t* q) {
    int v = front(q);
    q->size--;
    if (q->size) {
        q->_head++;
    }
    if (q->_head == q->_capacity) {
        q->_head = 0;
    }
    return v;
}

int front(queue_t* q) {
    return q->_array[q->_head];
}

char empty(queue_t* q) {
    return q->size ? 0 : 1;
}

void cleanup(queue_t* q) {
    free(q->_array);
    free(q);
}

int main() {
    int n;
    scanf("%d", &n);
    queue_t* q = make_queue();
    for (int i = 0; i < n; ++i) {
        char* str;
        scanf("%ms", &str);
        if (!strcmp(str, "ENQ")) {
            int x;
            scanf("%d", &x);
            push(q, x);
        } else if (!strcmp(str, "DEQ")) {
            printf("%d\n", pop(q));
        } else if (!strcmp(str, "EMPTY")) {
            if (empty(q)) {
                printf("true\n");
            } else {
                printf("false\n");
            }
        }
        free(str);
    }
    cleanup(q);
    return 0;
}
