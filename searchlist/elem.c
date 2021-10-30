
#include "elem.h"
#include <stdlib.h>

struct Elem* consf(struct Elem* list, float value) {
    struct Elem* new = malloc(sizeof(struct Elem));
    new->tag = FLOAT;
    new->tail = list;
    new->value.f = value;
    return new;
}

struct Elem* consi(struct Elem* list, int value) {
    struct Elem* new = malloc(sizeof(struct Elem));
    new->tag = INTEGER;
    new->tail = list;
    new->value.i = value;
    return new;
}

struct Elem* consl(struct Elem* list, struct Elem* value) {
    struct Elem* new = malloc(sizeof(struct Elem));
    new->tag = LIST;
    new->tail = list;
    new->value.list = value;
    return new;
}

void list_cleanup(struct Elem* list) {
    while (list) {
        if (list->tag == LIST) {
            list_cleanup(list->value.list);
        }
        struct Elem* temp = list->tail;
        free(list);
        list = temp;
    }
}
