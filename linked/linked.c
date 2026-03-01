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
    size_t  count;
    Node   *head;
    Node   *tail;
} Linked_List;


int main(void)
{
    Linked_List linked = {0};

    assert(linked.count == 0);
    ll_unshift(&linked, 1);
    ll_append(&linked, 10);
    ll_append(&linked, 100);
    ll_append(&linked, 1000);
    ll_append(&linked, 10000);
    ll_append(&linked, 100000);
    ll_append(&linked, 1000000);
    assert(linked.count == 7);

    assert(linked.head->value == 1);
    assert(ll_get(&linked, 1) == 10);
    assert(ll_get(&linked, 2) == 100);
    assert(ll_get(&linked, 3) == 1000);
    assert(ll_get(&linked, 4) == 10000);
    assert(ll_get(&linked, 5) == 100000);
    assert(linked.tail->value == 1000000);

    int tal[] = {1, 2, 3, 4};

    ll_append_many(&linked, tal, 4);
    assert(ll_get(&linked, 7) == 1);
    assert(ll_get(&linked, 8) == 2);
    assert(ll_get(&linked, 9) == 3);
    assert(linked.tail->value == 4);
    assert(linked.count == 11);

    ll_remove(&linked, 0);
    assert(ll_get(&linked, 0) == 10);
    assert(ll_get(&linked, 1) == 100);
    assert(linked.tail->value == 4);
    assert(linked.count == 10);

    assert(ll_pop(&linked) == 4);
    assert(linked.tail->value == 3);
    assert(linked.count == 9);

    ll_add(&linked, 0, -1);
    assert(linked.head->value == -1);
    assert(ll_get(&linked, 2) == 100);
    assert(linked.tail->value == 3);

    ll_foreach(pog, &linked) {
        printf("%d\n", pog->value);
    }

    return 0;
}
