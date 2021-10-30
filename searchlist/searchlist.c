
#include <stdio.h>
#include "elem.h"

struct Elem* searchlist(struct Elem* list, int k) {
    while (list) {
        if (list->tag == INTEGER && list->value.i == k) {
            return list;
        }
        list = list->tail;
    }
    return NULL;
}

int main() {
    struct Elem* nested_list = NULL;
    nested_list = cons(nested_list, 2);
    nested_list = cons(nested_list, 2.0f);

    struct Elem* list = NULL;
    list = cons(list, 1);
    list = cons(list, 1.0f);
    list = cons(list, nested_list);
    list = cons(list, 5);

    struct Elem* ans = searchlist(list, 1);
    printf("%d\n", ans->value.i);
    ans = searchlist(list, 2);
    printf("%p\n", (void*)ans);
    list_cleanup(list);
    return 0;
}
