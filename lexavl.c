#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>

#define VECTOR_DEFINE(name, type)                                              \
    typedef struct {                                                           \
        type* _array;                                                          \
        size_t _capacity;                                                      \
        size_t size;                                                           \
    } name

#define VECTOR_MAKE(name, type)                                                \
    (name) { malloc(sizeof(type*) * 10), 10, 0 }

#define VECTOR_PUSH(type, vector, value)                                       \
    {                                                                          \
        if ((vector).size == (vector)._capacity) {                             \
            (vector)._array = realloc((vector)._array,                         \
                                      (vector)._capacity * 2 * sizeof(type));  \
            (vector)._capacity *= 2;                                           \
        }                                                                      \
        (vector)._array[(vector).size] = value;                                \
        (vector).size++;                                                       \
    }

#define VECTOR_BACK(vector) ((vector)._array[(vector).size - 1])

#define VECTOR_POP(vector) ((vector)._array[--(vector).size])

#define VECTOR_EMPTY(vector) ((vector).size == 0)

#define VECTOR_CLEANUP(vector)                                                 \
    { free((vector)._array); }

struct node {
    char* k;
    int32_t v;
    struct node* left;
    struct node* right;
    struct node* prev;
    int32_t balance;
};

typedef struct node node_t;

typedef struct {
    node_t* root;
    size_t size;
} tree_t;

tree_t* tree_make();
node_t* tree_lookup(tree_t* tree, char* k);
void tree_replace_node(tree_t* tree, node_t* old, node_t* new);
void tree_insert(tree_t* tree, char* k, int32_t v);
void tree_balance(tree_t* tree, node_t* new);
void tree_rotate_left(tree_t* tree, node_t* x);
void tree_rotate_right(tree_t* tree, node_t* x);
void tree_cleanup(tree_t* tree);

tree_t* tree_make() {
    tree_t* new = malloc(sizeof(tree_t));
    new->root = NULL;
    new->size = 0;
    return new;
}

node_t* tree_lookup(tree_t* tree, char* k) {
    node_t* root = tree->root;
    while (root) {
        int cmp = strcmp(root->k, k);
        if (cmp == 0) {
            return root;
        }
        if (cmp < 0) {
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return NULL;
}

void tree_replace_node(tree_t* tree, node_t* old, node_t* new) {
    if (tree->root == old) {
        tree->root = new;
        if (new) {
            new->prev = NULL;
        }
        return;
    }
    if (old->prev->right == old) {
        old->prev->right = new;
    } else {
        old->prev->left = new;
    }
    if (new) {
        new->prev = old->prev;
    }
}

void tree_insert(tree_t* tree, char* k, int32_t v) {
    tree->size++;
    node_t* new = malloc(sizeof(node_t));
    new->k = k;
    new->v = v;
    new->left = NULL;
    new->right = NULL;
    if (!tree->root) {
        tree->root = new;
        new->prev = NULL;
        new->balance = 0;
        return;
    }
    node_t* root = tree->root;
    while (1) {
        if (strcmp(k, root->k) < 0) {
            if (!root->left) {
                root->left = new;
                new->prev = root;
                break;
            }
            root = root->left;
        } else {
            if (!root->right) {
                root->right = new;
                new->prev = root;
                break;
            }
            root = root->right;
        }
    }
    tree_balance(tree, new);
}

void tree_balance(tree_t* tree, node_t* new) {
    new->balance = 0;
    while (1) {
        node_t* prev = new->prev;
        if (!prev) {
            break;
        }
        if (new == prev->left) {
            prev->balance--;
            if (prev->balance == 0) {
                break;
            }
            if (prev->balance == -2) {
                if (new->balance == 1) {
                    tree_rotate_left(tree, new);
                }
                tree_rotate_right(tree, prev);
                break;
            }
        } else {
            prev->balance++;
            if (prev->balance == 0) {
                break;
            }
            if (prev->balance == 2) {
                if (new->balance == -1) {
                    tree_rotate_right(tree, new);
                }
                tree_rotate_left(tree, prev);
                break;
            }
        }
        new = prev;
    }
}

void tree_rotate_left(tree_t* tree, node_t* x) {
    node_t* y = x->right;
    tree_replace_node(tree, x, y);
    node_t* b = y->left;
    if (b) {
        b->prev = x;
    }
    x->right = b;
    x->prev = y;
    y->left = x;
    x->balance--;
    if (y->balance > 0) {
        x->balance -= y->balance;
    }
    y->balance--;
    if (x->balance < 0) {
        y->balance += x->balance;
    }
}

void tree_rotate_right(tree_t* tree, node_t* x) {
    node_t* y = x->left;
    tree_replace_node(tree, x, y);
    node_t* c = y->right;
    if (c) {
        c->prev = x;
    }
    x->left = c;
    x->prev = y;
    y->right = x;
    x->balance++;
    if (y->balance < 0) {
        x->balance -= y->balance;
    }
    y->balance++;
    if (x->balance > 0) {
        y->balance += x->balance;
    }
}

VECTOR_DEFINE(node_vector_t, node_t*);

void tree_cleanup(tree_t* tree) {
    node_t* root = tree->root;
    node_vector_t st = VECTOR_MAKE(node_vector_t, node_t*);
    VECTOR_PUSH(node_t*, st, root);
    while (!VECTOR_EMPTY(st)) {
        node_t* tmp = VECTOR_POP(st);
        if (tmp) {
            VECTOR_PUSH(node_t*, st, tmp->left);
            VECTOR_PUSH(node_t*, st, tmp->right);
            free(tmp->k);
            free(tmp);
        }
    }
    VECTOR_CLEANUP(st);
    free(tree);
}

typedef struct {
    enum { CONST, SPEC, IDENT } tag;
    int32_t value;
} token_t;

VECTOR_DEFINE(token_vector_t, token_t);

void tokenize(token_vector_t* tokens, int32_t (*const stream_peek)(),
              int32_t (*const stream_next)());

/* void := */
/* sentence := spaces lexeme sentence | spaces | void */
void sentence(token_vector_t* tokens, tree_t* identifiers,
              int32_t (*const stream_peek)(), int32_t (*const stream_next)());
/* spaces := SPACE* */
void spaces(int32_t (*const stream_peek)(), int32_t (*const stream_next)());
/* lexeme := constant | spec | identifier */
void lexeme(token_t* token, tree_t* identifiers, int32_t (*const stream_peek)(),
            int32_t (*const stream_next)());
/* constant := DIGIT+ */
void constant(token_t* token, int32_t (*const stream_peek)(),
              int32_t (*const stream_next)());
/* spec := + | - | * | / | ( | ) */
void spec(token_t* token, int32_t (*const stream_peek)(),
          int32_t (*const stream_next)());
/* identifier := LETTER+ DIGIT* identifier | LETTER+ DIGIT* */
void identifier(token_t* token, tree_t* identifiers,
                int32_t (*const stream_peek)(), int32_t (*const stream_next)());

void tokenize(token_vector_t* tokens, int32_t (*const stream_peek)(),
              int32_t (*const stream_next)()) {
    tree_t* identifiers = tree_make();
    sentence(tokens, identifiers, stream_peek, stream_next);
    tree_cleanup(identifiers);
}

static const char SPEC_LIST[6] = { '+', '-', '*', '/', '(', ')' };

int32_t isspec(int32_t sym) {
    for (size_t i = 0; i < sizeof(SPEC_LIST); ++i) {
        if (sym == SPEC_LIST[i]) {
            return 1;
        }
    }
    return 0;
}

void sentence(token_vector_t* tokens, tree_t* identifiers,
              int32_t (*const stream_peek)(), int32_t (*const stream_next)()) {
    spaces(stream_peek, stream_next);
    token_t new;
    lexeme(&new, identifiers, stream_peek, stream_next);
    VECTOR_PUSH(token_t, *tokens, new);
    if (stream_peek() != EOF && stream_peek() != '\n') {
        sentence(tokens, identifiers, stream_peek, stream_next);
    }
}

void spaces(int32_t (*const stream_peek)(), int32_t (*const stream_next)()) {
    while (stream_peek() == ' ') {
        stream_next();
    }
}

void lexeme(token_t* token, tree_t* identifiers, int32_t (*const stream_peek)(),
            int32_t (*const stream_next)()) {
    if (isdigit(stream_peek())) {
        constant(token, stream_peek, stream_next);
    } else if (isspec(stream_peek())) {
        spec(token, stream_peek, stream_next);
    } else if (isalpha(stream_peek())) {
        identifier(token, identifiers, stream_peek, stream_next);
    }
}

void constant(token_t* token, int32_t (*const stream_peek)(),
              int32_t (*const stream_next)()) {
    token->tag = CONST;
    token->value = 0;
    while (isdigit(stream_peek())) {
        token->value *= 10;
        token->value += stream_next() - '0';
    }
}

void spec(token_t* token, int32_t (*const stream_peek)(),
          int32_t (*const stream_next)()) {
    token->tag = SPEC;
    for (size_t i = 0; i < sizeof(SPEC_LIST); ++i) {
        if (stream_peek() == SPEC_LIST[i]) {
            token->value = (int32_t)i;
            stream_next();
            break;
        }
    }
}

VECTOR_DEFINE(char_vector_t, char);

void identifier(token_t* token, tree_t* identifiers,
                int32_t (*const stream_peek)(),
                int32_t (*const stream_next)()) {
    token->tag = IDENT;
    char_vector_t str = VECTOR_MAKE(char_vector_t, char);
    while (isalnum(stream_peek())) {
        VECTOR_PUSH(char, str, (char)stream_next());
    }
    VECTOR_PUSH(char, str, '\0');
    token->value = 0;
    node_t* node;
    if ((node = tree_lookup(identifiers, str._array))) {
        token->value = node->v;
        VECTOR_CLEANUP(str);
    } else {
        token->value = (int32_t)identifiers->size;
        tree_insert(identifiers, str._array, token->value);
    }
}

static int32_t sym;

static inline int32_t stream_peek() { return sym; }

static inline int32_t stream_next() {
    int32_t tmp = sym;
    sym = getc(stdin);
    return tmp;
}

void token_vector_output(const token_vector_t vector) {
    for (size_t i = 0; i < vector.size; ++i) {
        switch (vector._array[i].tag) {
        case CONST:
            printf("CONST %"PRId32"\n", vector._array[i].value);
            break;
        case SPEC:
            printf("SPEC %"PRId32"\n", vector._array[i].value);
            break;
        case IDENT:
            printf("IDENT %"PRId32"\n", vector._array[i].value);
            break;
        }
    }
}

int32_t main() {
    size_t n;
    scanf("%zu", &n);
    stream_next();
    stream_next();
    token_vector_t tokens = VECTOR_MAKE(token_vector_t, token_t);
    tokenize(&tokens, stream_peek, stream_next);
    token_vector_output(tokens);
    VECTOR_CLEANUP(tokens);
    return 0;
}
