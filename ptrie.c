
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int v;
    struct trie_t* arcs[26];
} trie_t;

trie_t* make_trie();
void trie_insert(trie_t* trie, char* str);
void trie_delete(trie_t* trie, char* str);
int trie_prefix(trie_t* trie, char* str);
void trie_cleanup(trie_t* trie);

trie_t* make_trie() {
    trie_t* new = malloc(sizeof(trie_t));
    new->v = 0;
    for (int i = 0; i < 26; ++i) {
        new->arcs[i] = NULL;
    }
    return new;
}

void trie_insert(trie_t* trie, char* str) {
    trie->v++;
    while (*str != '\0') {
        int index = *str - 'a';
        if (!trie->arcs[index]) {
            trie->arcs[index] = make_trie();
        }
        trie = trie->arcs[index];
        trie->v++;
        str++;
    }
}

void trie_delete(trie_t* trie, char* str) {
    trie->v--;
    while (*str != '\0') {
        int index = *str - 'a';
        trie = trie->arcs[index];
        trie->v--;
        str++;
    }
}

int trie_prefix(trie_t* trie, char* str) {
    while (*str != '\0') {
        int index = *str - 'a';
        trie = trie->arcs[index];
        if (!trie) {
            return 0;
        }
        str++;
    }
    return trie->v;
}

void trie_cleanup(trie_t* trie) {
    if (trie) {
        for (int i = 0; i < 26; ++i) {
            trie_cleanup(trie->arcs[i]);
        }
        free(trie);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    trie_t* trie = make_trie();
    for (int i = 0; i < n; ++i) {
        char* command;
        scanf("%ms", &command);
        if (!strcmp(command, "INSERT")) {
            char* str;
            scanf("%ms", &str);
            trie_insert(trie, str);
            free(str);
        } else if (!strcmp(command, "DELETE")) {
            char* str;
            scanf("%ms", &str);
            trie_delete(trie, str);
            free(str);
        } else if (!strcmp(command, "PREFIX")) {
            char* str;
            scanf("%ms", &str);
            printf("%d\n", trie_prefix(trie, str));
            free(str);
        }
        free(command);
    }
    trie_cleanup(trie);
    return 0;
}
