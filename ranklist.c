
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 17
#define INF 1000000001

struct node {
    int k;
    char* v;
    struct node** next;
    int* span;
};

typedef struct node skiplist_t;

skiplist_t* skiplist_make();
skiplist_t* skiplist_succ(skiplist_t* x);
void skiplist_skip(skiplist_t* l, int k, skiplist_t** p);
char* skiplist_lookup(skiplist_t* l, int k);
void skiplist_insert(skiplist_t* l, int k, char* v);
void skiplist_delete(skiplist_t* l, int k);
int skiplist_rank(skiplist_t* l, int k);
void skiplist_cleanup(skiplist_t* l);

skiplist_t* skiplist_make() {
    skiplist_t* new = malloc(sizeof(skiplist_t));
    new->next = calloc(M, sizeof(skiplist_t*));
    new->span = calloc(M, sizeof(int));
    new->k = -INF;
    new->v = NULL;
    return new;
}

skiplist_t* skiplist_succ(skiplist_t* x) {
    return x->next[0];
}

int skiplist_rank(skiplist_t* l, int k) {
    if (k == -INF) {
        return -1;
    }
    int index = 0;
    for (long i = (long)M - 1; i >= 0; --i) {
        while (l->next[i] && l->next[i]->k < k) {
            index += l->span[i];
            l = l->next[i];
        }
    }
    return index;
}

void skiplist_skip(skiplist_t* l, int k, skiplist_t** p) {
    for (long i = (long)M - 1; i >= 0; --i) {
        while (l->next[i] && l->next[i]->k < k) {
            l = l->next[i];
        }
        p[i] = l;
    }
}

char* skiplist_lookup(skiplist_t* l, int k) {
    skiplist_t* p[M];
    skiplist_skip(l, k, p);
    skiplist_t* x = skiplist_succ(p[0]);
    return x->v;
}

void skiplist_insert(skiplist_t* l, int k, char* v) {
    skiplist_t* p[M];
    skiplist_skip(l, k, p);
    skiplist_t* x = skiplist_make();
    x->v = v;
    x->k = k;
    long long r = rand() * 2ll;
    int rank_x = skiplist_rank(l, p[0]->k) + 1;
    int i;
    for (i = 0; i < M && r % 2 == 0; ++i) {
        x->next[i] = p[i]->next[i];
        p[i]->next[i] = x;
        int rank_pi = skiplist_rank(l, p[i]->k);
        x->span[i] = p[i]->span[i] + 1 - (rank_x - rank_pi);
        p[i]->span[i] = rank_x - rank_pi;
        r /= 2;
    }
    for (; i < M; ++i) {
        p[i]->span[i]++;
    }
}

void skiplist_delete(skiplist_t* l, int k) {
    skiplist_t* p[M];
    skiplist_skip(l, k, p);
    skiplist_t* x = skiplist_succ(p[0]);
    int i;
    for (i = 0; i < M && p[i]->next[i] == x; ++i) {
        p[i]->span[i] += x->span[i] - 1;
        p[i]->next[i] = x->next[i];
    }
    for (; i < M; ++i) {
        p[i]->span[i]--;
    }
    free(x->v);
    free(x->next);
    free(x->span);
    free(x);
}

void skiplist_cleanup(skiplist_t* l) {
    while (l) {
        skiplist_t* tmp = l->next[0];
        if (l->v) {
            free(l->v);
        }
        free(l->next);
        free(l->span);
        free(l);
        l = tmp;
    }
}

int main() {
    size_t n;
    scanf("%zu", &n);
    skiplist_t* arr = skiplist_make();
    for (size_t i = 0; i < n; ++i) {
        char op[10];
        scanf("%s", op);
        if (strcmp(op, "INSERT") == 0) {
            int k;
            char* v = malloc(11);
            scanf("%d%s", &k, v);
            skiplist_insert(arr, k, v);
        } else if (strcmp(op, "LOOKUP") == 0) {
            int k;
            scanf("%d", &k);
            printf("%s\n", skiplist_lookup(arr, k));
        } else if (strcmp(op, "DELETE") == 0) {
            int k;
            scanf("%d", &k);
            skiplist_delete(arr, k);
        } else if (strcmp(op, "RANK") == 0) {
            int k;
            scanf("%d", &k);
            printf("%d\n", skiplist_rank(arr, k));
        }
    }
    skiplist_cleanup(arr);
    return 0;
}
