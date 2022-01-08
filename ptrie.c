
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trie {
    int v;
    int word;
    struct trie* arcs[26];
};

typedef struct trie trie_t;

trie_t* make_trie();
char trie_contains(trie_t* trie, char* str);
void trie_insert(trie_t* trie, char* str);
void trie_delete(trie_t* trie, char* str);
int trie_prefix(trie_t* trie, char* str);
void trie_cleanup(trie_t* trie);

trie_t* make_trie() {
    trie_t* new = malloc(sizeof(trie_t));
    new->v = 0;
    new->word = 0;
    for (int i = 0; i < 26; ++i) {
        new->arcs[i] = NULL;
    }
    return new;
}

char trie_contains(trie_t* trie, char* str) {
    while (*str != '\0') {
        if (!trie->arcs[*str - 'a']) {
            return 0;
        }
        trie = trie->arcs[*str - 'a'];
        str++;
    }
    return trie->word == 1;
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
    trie->word = 1;
}

void trie_delete(trie_t* trie, char* str) {
    trie->v--;
    while (*str != '\0') {
        int index = *str - 'a';
        trie = trie->arcs[index];
        trie->v--;
        str++;
    }
    trie->word = 0;
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
            if (!trie_contains(trie, str)) {
                trie_insert(trie, str);
            }
            free(str);
        } else if (!strcmp(command, "DELETE")) {
            char* str;
            scanf("%ms", &str);
            if (trie_contains(trie, str)) {
                trie_delete(trie, str);
            }
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
