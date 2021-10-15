
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* prev;
} node;

typedef struct {
    node* begin;
    node* end;
} queue;

queue* queue_make() {
    queue* p = malloc(sizeof(queue));
    p->begin = NULL;
    p->end = NULL;
    return p;
}

void queue_cleanup(queue* p) {
    if (p) {
        while (p->end) {
            node* temp = p->end->prev;
            free(p->end);
            p->end = temp;
        }
        free(p);
    }
}

void queue_push(queue* p, int value) {
    node* new = malloc(sizeof(node));
    new->value = value;
    new->prev = NULL;
    if (p->begin) {
        p->begin->prev = new;
        p->begin = new;
    } else {
        p->begin = new;
        p->end = new;
    }
}

void queue_pop(queue* p) {
    if (p->begin == p->end) {
        free(p->end);
        p->begin = NULL;
        p->end = NULL;
    } else {
        node* temp = p->end->prev;
        free(p->end);
        p->end = temp;
    }
}

int queue_back(queue* p) {
    return p->end->value;
}

int main() {
    int n;
    int k;
    scanf("%d%d", &n, &k);
    queue* queue = queue_make();
    long sum = 0;
    for (int i = 0; i < k; ++i) {
        int num;
        scanf("%d", &num);
        queue_push(queue, num);
        sum += num;
    }
    long max_sum = sum;
    long ans = 0;
    for (int i = 0; i < n - k; ++i) {
        int num;
        scanf("%d", &num);
        sum += num;
        sum -= queue_back(queue);
        if (sum > max_sum) {
            max_sum = sum;
            ans = i + 1;
        }
        queue_pop(queue);
        queue_push(queue, num);
    }
    printf("%ld\n", ans);
    queue_cleanup(queue);
    return 0;
}
