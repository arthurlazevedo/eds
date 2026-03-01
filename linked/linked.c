#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "linked.h"

typedef struct Node Node;

struct Node {
    Node  *prev;
    Node  *next;
    int    value;
};

typedef struct {
    size_t  size;
    Node   *head;
    Node   *tail;
} Linked_List;


int main(void)
{
    Linked_List linked = {0};
    Linked_List *ll = &linked;

    ll_add_first(&linked, 1);
    assert(linked.size == 1);
    assert(linked.head->value == 1);

    ll_remove_head(&linked);
    assert(linked.size == 0);
    assert(linked.head == NULL);

    ll_add_last(&linked, 1);
    assert(linked.size == 1);
    assert(linked.head->value == 1);

    ll_add_last(&linked, 2);
    assert(linked.size == 2);
    assert(linked.head->next->value == 2);

    assert(ll_get(&linked, 1) == 2);

    return 0;
}
