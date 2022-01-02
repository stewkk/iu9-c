
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Elem {
    struct Elem *next;
    char *word;
    size_t len;
};

struct Elem* list_make();
struct Elem* list_push_front(struct Elem* list, char* str);
void list_output(struct Elem* list);
void list_cleanup(struct Elem* list);

struct Elem* list_make() {
    return NULL;
}

struct Elem* list_push_front(struct Elem* list, char* str) {
    struct Elem* new = malloc(sizeof(struct Elem));
    new->word = str;
    new->next = list;
    new->len = strlen(str);
    return new;
}

void list_output(struct Elem* list) {
    while (list) {
        printf("%s ", list->word);
        list = list->next;
    }
    printf("\n");
}

void list_cleanup(struct Elem* list) {
    while (list) {
        struct Elem* next = list->next;
        free(list->word);
        free(list);
        list = next;
    }
}

void swap(struct Elem* a, struct Elem* b) {
    size_t temp = a->len;
    a->len = b->len;
    b->len = temp;
    char* temp2 = a->word;
    a->word = b->word;
    b->word = temp2;
}

struct Elem* bsort(struct Elem *list) {
    struct Elem* bound = NULL;
    while (bound != list) {
        struct Elem* i = list;
        while (i->next != bound) {
          if (i->next->len < i->len) {
              swap(i->next, i);
          }
          i = i->next;
        }
        bound = i;
    }
    return list;
}

int main() {
    struct Elem* list = list_make();
    char* word;
    while (scanf("%ms", &word) != EOF) {
        list = list_push_front(list, word);
    }
    list = bsort(list);
    list_output(list);
    list_cleanup(list);
    return 0;
}
