
#ifndef ELEM_H_INCLUDED
#define ELEM_H_INCLUDED

struct Elem {
    /* «Тег», описывающий тип значения в «головe» списка */
    enum { INTEGER, FLOAT, LIST } tag;

    /* Само значение в «голове» списка */
    union {
        int i;
        float f;
        struct Elem *list;
    } value;

    /* Указатель на «хвост» списка */
    struct Elem *tail;
};

struct Elem* consf(struct Elem* list, float value);
struct Elem* consi(struct Elem* list, int value);
struct Elem* consl(struct Elem* list, struct Elem* value);

#define cons(LIST, X) _Generic((X), \
                               float: consf,       \
                               int: consi,         \
                               struct Elem*: consl \
)(LIST, X)

void list_cleanup(struct Elem* list);

#endif
