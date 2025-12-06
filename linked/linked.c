#include <linked.h>
#include <stdlib.h>
#include <assert.h>


static void set_head_tail(Linked_List* ll, Node* node)
{
    ll->head = node;
    ll->tail = node;
}


bool ll_is_empty(Linked_List* ll)
{
    return ll->head == NULL;
}


void ll_add_first(Linked_List* ll, int value)
{
    Node* new_node = NULL;
    set_node(new_node, value);
    
    if (ll_is_empty(ll)) {
        set_head_tail(ll, new_node);
    } else {
        ll->head->prev = (struct Node*) new_node;
        new_node->next = (struct Node*) ll->head;
        ll->head = new_node;
    }

    ll->size++;
}


void ll_add_last(Linked_List* ll, int value)
{
    Node* new_node = NULL;
    set_node(new_node, value);

    if (ll_is_empty(ll)) {
        set_head_tail(ll, new_node);
    } else {
        ll->tail->next = (struct Node*) new_node;
        new_node->prev = (struct Node*) ll->tail;
        ll->tail = new_node;
    }

    ll->size++;
}


bool ll_add(Linked_List* ll, int value, size_t index)
{
    if (index >= ll->size) return false;

    if (index == 0 || ll_is_empty(ll)) {
        ll_add_first(ll, value);        
        return true;
    }

    Node* new_node = NULL;
    set_node(new_node, value);

    Node* aux = ll->head;
    for (size_t i = 1; i < index; i++) aux = (Node*) aux->next;

    new_node->next = aux->next;
    new_node->prev = (struct Node*) aux;
    aux->next = (struct Node*) new_node;
    ((Node*) new_node->next)->prev = (struct Node*) new_node;

    ll->size++;
}


bool ll_remove_first(Linked_List* ll)
{
    if (ll_is_empty(ll)) return false;

    if (ll->size == 1) {
        free(ll->head);
        set_head_tail(ll, NULL);
    } else {
        ll->head = (Node*) ll->head->next;
        free(ll->head->prev);
        ll->head->prev = NULL;
    }

    ll->size--;
    return true;
}


bool ll_remove_last(Linked_List* ll)
{
    if (ll_is_empty(ll)) return false;

    if (ll->size == 1) {
        free(ll->tail);
        set_head_tail(ll, NULL);
    } else {
        ll->tail = (Node*) ll->tail->prev;
        free(ll->tail->next);
        ll->tail->next = NULL;
    }

    ll->size--;
    return true;
}


bool ll_remove(Linked_List* ll, size_t index)
{
    if (ll_is_empty(ll) || index >= ll->size) return false;

    if (index == 0) {
        ll_remove_first(ll);
        return true;
    }

    if (index == ll->size - 1) {
        ll_remove_last(ll);
        return true;
    }

    Node* aux = ll->head;
    for (size_t i = 1; i <= index; i++) aux = (Node*) aux->next;

    ((Node*) aux->prev)->next = aux->next;
    ((Node*) aux->next)->prev = aux->prev;
    free(aux);

    ll->size--;
    return true;
}


int* ll_get_first(Linked_List* ll)
{
    if (ll_is_empty(ll)) return NULL;

    return &(ll->head->value);
}


int* ll_get_last(Linked_List* ll)
{
    if (ll_is_empty(ll)) return NULL;

    return &(ll->tail->value);
}


int* ll_get(Linked_List* ll, size_t index)
{
    if (index >= ll->size) return NULL;
    if (index == 0) return ll_get_first(ll);
    if (index == ll->size - 1) return ll_get_last(ll);

    Node* aux = ll->head;
    for (size_t i = 1; i <= index; i++) aux = (Node*) aux->next;

    return &(aux->value);
}


int ll_index_of(Linked_List* ll, int value)
{
    Node* aux = ll->head;
    int idx = 0;

    while (aux) {
        if (aux->value == value) return idx;
        aux = (Node*) aux->next;
        idx++;
    }
    
    return -1;
}


int ll_last_index_of(Linked_List* ll, int value)
{
    Node* aux = ll->tail;
    int idx = ll->size - 1;

    while (aux) {
        if (aux->value == value) return idx;
        aux = (Node*) aux->prev;
        idx--;
    }

    return -1;
}


bool ll_contains(Linked_List* ll, int value)
{
    return ll_index_of(ll, value) != -1;
}


int main(void)
{
    Linked_List ll = {0};

    ll_add_first(&ll, 0);
    assert(ll.size == 1);
    assert(!ll_is_empty(&ll));
    assert(*ll_get_first(&ll) == 0);

    ll_remove_first(&ll);
    assert(ll.size == 0);
    assert(ll_is_empty(&ll));
    assert(ll_get_first(&ll) == NULL);

    return 0;
}
