#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int value;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    size_t size;
    Node* head;
    Node* tail;
} Linked_List;

typedef struct {
    char* data;
    size_t len;
    size_t cap;
} String_Builder;

#define set_node(node, value) \
    do { \
        (node) = malloc(sizeof(Node)); \
        (node)->value = value; \
    } while (0);


bool (ll_is_empty)     (Linked_List*);

void (ll_add_first)    (Linked_List*, int);
void (ll_add_last)     (Linked_List*, int);
bool (ll_add)          (Linked_List*, int, size_t);

bool (ll_remove_first) (Linked_List*);
bool (ll_remove_last)  (Linked_List*);
bool (ll_remove)       (Linked_List*, size_t);

int* (ll_get_first)    (Linked_List*);
int* (ll_get_last)     (Linked_List*);
int* (ll_get)          (Linked_List*, size_t);

int (ll_index_of)      (Linked_List*, int);
int (ll_last_index_of) (Linked_List*, int);
bool (ll_contains)     (Linked_List*, int);

// TODO: to_string
char* (ll_to_string)   (Linked_List*);