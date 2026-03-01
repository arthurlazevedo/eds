#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>


#define set_head_tail(ll, node)                             \
    do {                                                    \
        (ll)->head = node;                                  \
        (ll)->tail = node;                                  \
    } while (0)


#define set_node(node, val)                                 \
    do {                                                    \
        (node) = malloc(sizeof(*(node)));                   \
        (node)->value = val;                                \
    } while (0)


#define ll_add_first(ll, val)                               \
    do {                                                    \
        typeof((ll)->head) new_node = NULL;                 \
        set_node(new_node, val);                            \
                                                            \
        if ((ll)->size == 0) {                              \
            set_head_tail(ll, new_node);                    \
        } else {                                            \
            (ll)->head->prev = new_node;                    \
            new_node->next = (ll)->head;                    \
            (ll)->head = new_node;                          \
        }                                                   \
                                                            \
        (ll)->size++;                                       \
    } while (0)


#define ll_add_last(ll, val)                                \
    do {                                                    \
        typeof((ll)->head) new_node = NULL;                 \
        set_node(new_node, val);                            \
                                                            \
        if ((ll)->size == 0) {                              \
            set_head_tail((ll), new_node);                  \
        } else {                                            \
            (ll)->tail->next = new_node;                    \
            new_node->prev = (ll)->tail;                    \
            (ll)->tail = new_node;                          \
        }                                                   \
                                                            \
        (ll)->size++;                                       \
    } while (0)


#define ll_add(ll, val, index)                              \
    do {                                                    \
        if (index == 0 || (ll)->size == 0)                  \
            ll_add_first(ll, val);                          \
                                                            \
        assert(index < (ll)->size);                         \
                                                            \
        typeof((ll)->head) new_node = NULL;                 \
        set_node(new_node, (val));                          \
                                                            \
        typeof((ll)->head) aux = (ll)->head;                \
        for (size_t i = 1; i < index; i++)                  \
            aux = aux->next;                                \
                                                            \
        new_node->next = aux->next;                         \
        new_node->prev = aux;                               \
        aux->next = new_node;                               \
        new_node->next->prev = new_node;                    \
                                                            \
        (ll)->size++;                                       \
    } while (0)


#define ll_remove_head(ll)                                  \
    do {                                                    \
        assert((ll)->size);                                 \
                                                            \
        if ((ll)->size == 1) {                              \
            free((ll)->head);                               \
            set_head_tail((ll), NULL);                      \
        } else {                                            \
            (ll)->head = (ll)->head->next;                  \
            free((ll)->head->prev);                         \
            (ll)->head->prev = NULL;                        \
        }                                                   \
                                                            \
        (ll)->size--;                                       \
    } while (0)


#define ll_remove_tail(ll)                                  \
    do {                                                    \
        assert((ll)->size);                                 \
                                                            \
        if ((ll)->size == 1) {                              \
            free((ll)->tail);                               \
            set_head_tail(ll, NULL);                        \
        } else {                                            \
            (ll)->tail = (ll)->tail->prev;                  \
            free((ll)->tail->next);                         \
            (ll)->tail->next = NULL;                        \
        }                                                   \
                                                            \
        (ll)->size--;                                       \
    } while (0)


#define ll_remove(ll, index)                                \
    do {                                                    \
        assert((ll)->size && index < (ll)->size);           \
                                                            \
        if ((index) == 0)                                   \
            ll_remove_first(ll);                            \
                                                            \
        if ((index) == (ll)->size - 1)                      \
            ll_remove_last(ll);                             \
                                                            \
        typeof((ll)->head) aux = (ll)->head;                \
        for (size_t i = 1; i <= index; i++)                 \
            aux = aux->next;                                \
                                                            \
        aux->prev->next = aux->next;                        \
        aux->next->prev = aux->prev;                        \
        free(aux);                                          \
                                                            \
        (ll)->size--;                                       \
    } while (0)


// o nome disso é statement expressions, muito útil
#define ll_get(ll, index)                                   \
    ({                                                      \
        assert((ll)->size && index < (ll)->size);           \
        typeof((ll)->head->value) res;                      \
        if (index == (ll)->size - 1) {                      \
            res = (ll)->tail->value;                        \
        } else {                                            \
            typeof((ll)->head) aux = (ll)->head;            \
            for (size_t i = 1; i <= index; i++)             \
                aux = aux->next;                            \
                                                            \
            (res) = aux->value;                             \
        }                                                   \
        res;                                                \
    })
