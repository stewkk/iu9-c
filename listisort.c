
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

struct Elem {
    struct Elem *prev, *next;
    int v;
};

typedef struct Elem list_t;

list_t* list_make();
void list_insert_before_head(list_t* list, int v);
void list_sort(list_t* list);
void list_output(list_t* list);
void list_cleanup(list_t* list);

list_t* list_make() {
    list_t* new = malloc(sizeof(list_t));
    new->next = new;
    new->prev = new;
    new->v = INF;
    return new;
}

void list_insert_before_head(list_t* list, int v) {
    list_t* new = malloc(sizeof(list_t));
    new->next = list->next;
    new->prev = list;
    new->v = v;
    list->next->prev = new;
    list->next = new;
}

void list_sort(list_t* list) {
    list_t* i = list->next->next;
    while (i != list) {
        list_t* temp = i->next;
        int elem = i->v;
        list_t* loc = i->prev;
        while (loc != list && loc->v > elem) {
            loc = loc->prev;
        }
        i->prev->next = i->next;
        i->next->prev = i->prev;
        i->prev = loc;
        i->next = loc->next;
        loc->next->prev = i;
        loc->next = i;
        i = temp;
    }
}

void list_output(list_t* list) {
    list_t* nil = list;
    list = list->next;
    while (list != nil) {
        printf("%d ", list->v);
        list = list->next;
    }
}

void list_cleanup(list_t* list) {
    list_t* nil = list;
    list = list->next;
    while (list != nil) {
        list_t* temp = list;
        list = list->next;
        free(temp);
    }
    free(nil);
}

int main() {
    int n;
    scanf("%d", &n);
    list_t* list = list_make();
    for (int i = 0; i < n; ++i) {
        int v;
        scanf("%d", &v);
        list_insert_before_head(list, v);
    }
    list_sort(list);
    list_output(list);
    list_cleanup(list);
    return 0;
}
