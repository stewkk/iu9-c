
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int k;
    char* v;
    struct node* left;
    struct node* right;
    struct node* prev;
    int count;
};

typedef struct node node_t;

typedef struct {
    node_t* root;
} tree_t;

tree_t* tree_make();
node_t* tree_lookup(tree_t* tree, int k);
void tree_insert(tree_t* tree, int k, char* v);
void tree_delete(tree_t* tree, int k);
void tree_replace_node(tree_t* tree, node_t* old, node_t* new);
char* tree_search(tree_t* tree, int k);
void tree_cleanup(tree_t* tree);

tree_t* tree_make() {
    tree_t* new = malloc(sizeof(tree_t));
    new->root = NULL;
    return new;
}

node_t* tree_lookup(tree_t* tree, int k) {
    node_t* root = tree->root;
    while (root) {
        if (root->k == k) {
            return root;
        }
        if (k > root->k) {
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return NULL;
}

char* tree_search(tree_t* tree, int k) {
    node_t* root = tree->root;
    while (root->count != k) {
        if (k > root->count) {
            k -= root->count + 1;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return root->v;
}

void tree_insert(tree_t* tree, int k, char* v) {
    node_t* new = malloc(sizeof(node_t));
    new->k = k;
    new->v = v;
    new->count = 0;
    new->left = NULL;
    new->right = NULL;
    if (!tree->root) {
        tree->root = new;
        new->prev = NULL;
        return;
    }
    node_t* root = tree->root;
    while (1) {
        if (k < root->k) {
            if (!root->left) {
              root->count++;
              root->left = new;
              new->prev = root;
              break;
            }
            root->count++;
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

node_t* tree_get_next(node_t* node) {
    node = node->right;
    while (node->left) {
        node = node->left;
    }
    return node;
}

void tree_decrease_count(node_t* node) {
    while (node && node->prev) {
        if (node->prev->left == node) {
            node->prev->count--;
        }
        node = node->prev;
    }
}

void tree_node_cleanup(node_t* node) {
    free(node->v);
    free(node);
}

void tree_delete(tree_t* tree, int k) {
    node_t* to_remove = tree_lookup(tree, k);
    if (!to_remove->left && !to_remove->right) {
        tree_decrease_count(to_remove);
        tree_replace_node(tree, to_remove, NULL);
    } else if (!to_remove->left) {
        tree_decrease_count(to_remove);
        tree_replace_node(tree, to_remove, to_remove->right);
    } else if (!to_remove->right) {
        tree_decrease_count(to_remove);
        tree_replace_node(tree, to_remove, to_remove->left);
    } else {
        node_t *next = tree_get_next(to_remove);
        tree_decrease_count(next);
        tree_replace_node(tree, next, next->right);
        tree_replace_node(tree, to_remove, next);
        next->count = to_remove->count;
        next->left = to_remove->left;
        next->left->prev = next;
        if (to_remove->right) {
          next->right = to_remove->right;
          next->right->prev = next;
        }
    }
    tree_node_cleanup(to_remove);
}

typedef struct {
    node_t** _array;
    size_t _capacity;
    size_t size;
} stack_t;

stack_t* stack_make();
void stack_push(stack_t* st, node_t* val);
node_t* stack_pop(stack_t* st);
node_t* stack_top(stack_t* st);
char stack_empty(stack_t* st);
void stack_cleanup(stack_t* st);

stack_t* stack_make() {
    stack_t* new = malloc(sizeof(stack_t));
    new->_capacity = 10;
    new->size = 0;
    new->_array = malloc(sizeof(node_t*) * 10);
    return new;
}

void stack_push(stack_t* st, node_t* val) {
    if (st->size == st->_capacity) {
        st->_array = realloc(st->_array, st->_capacity * 2 * sizeof(node_t*));
        st->_capacity *= 2;
    }
    st->_array[st->size] = val;
    st->size++;
}

node_t* stack_pop(stack_t* st) {
    node_t* val = stack_top(st);
    st->size--;
    return val;
}

node_t* stack_top(stack_t* st) {
    return st->_array[st->size - 1];
}

char stack_empty(stack_t* st) {
    return st->size == 0;
}

void stack_cleanup(stack_t* st) {
    free(st->_array);
    free(st);
}

void tree_cleanup(tree_t* tree) {
    node_t* root = tree->root;
    stack_t* st = stack_make();
    stack_push(st, root);
    while (!stack_empty(st)) {
        node_t* tmp = stack_pop(st);
        if (tmp) {
            stack_push(st, tmp->left);
            stack_push(st, tmp->right);
            free(tmp->v);
            free(tmp);
        }
    }
    stack_cleanup(st);
    free(tree);
}

int main() {
    size_t n;
    scanf("%zu", &n);
    tree_t* tree = tree_make();
    for (size_t i = 0; i < n; ++i) {
        char op[10];
        scanf("%s", op);
        if (strcmp(op, "INSERT") == 0) {
            int k;
            char* v = malloc(11);
            scanf("%d%s", &k, v);
            tree_insert(tree, k, v);
        } else if (strcmp(op, "LOOKUP") == 0) {
            int k;
            scanf("%d", &k);
            printf("%s\n", tree_lookup(tree, k)->v);
        } else if (strcmp(op, "DELETE") == 0) {
            int k;
            scanf("%d", &k);
            tree_delete(tree, k);
        } else if (strcmp(op, "SEARCH") == 0) {
            int k;
            scanf("%d", &k);
            printf("%s\n", tree_search(tree, k));
        }
    }
    tree_cleanup(tree);
    return 0;
}
