#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef dll
#define dll 1
#endif

#ifndef REMOVED
#define REMOVED(node) (node)->value
#endif

#define Node(ll) typeof((ll)->head)
#define NodeVal(ll) typeof((ll)->head->value)


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


#define ll_is_empty(ll) (ll)->count == 0


#define ll_foreach(item, ll) for (Node(ll) item = (ll)->head; item != NULL; item = item->next)


#define ll_unshift(ll, val)                                 \
    do {                                                    \
        Node(ll) new_node = NULL;                           \
        set_node(new_node, val);                            \
                                                            \
        if ((ll)->count == 0) {                             \
            set_head_tail(ll, new_node);                    \
        } else {                                            \
            if (dll) (ll)->head->prev = new_node;           \
            new_node->next = (ll)->head;                    \
            (ll)->head = new_node;                          \
        }                                                   \
                                                            \
        (ll)->count++;                                      \
    } while (0)


#define ll_add(ll, idx, e)                                  \
    do {                                                    \
        if (idx == 0 || (ll)->count == 0)                   \
            ll_unshift(ll, e);                              \
        else {                                              \
            assert(idx > 0 && idx < (ll)->count);           \
                                                            \
            Node(ll) new_node = NULL;                       \
            set_node(new_node, e);                          \
                                                            \
            Node(ll) aux = (ll)->head;                      \
            for (size_t i = 1; i < idx; i++)                \
                aux = aux->next;                            \
                                                            \
            new_node->next = aux->next;                     \
            if (dll) new_node->prev = aux;                  \
            aux->next = new_node;                           \
            if (dll) new_node->next->prev = new_node;       \
                                                            \
            (ll)->count++;                                  \
        }                                                   \
    } while (0)


#define ll_append(ll, val)                                  \
    do {                                                    \
        Node(ll) new_node = NULL;                           \
        set_node(new_node, val);                            \
                                                            \
        if ((ll)->count == 0) {                             \
            set_head_tail((ll), new_node);                  \
        } else {                                            \
            (ll)->tail->next = new_node;                    \
            if (dll) new_node->prev = (ll)->tail;           \
            (ll)->tail = new_node;                          \
        }                                                   \
                                                            \
        (ll)->count++;                                      \
    } while (0)


#define ll_append_many(ll, many, len)                       \
    do {                                                    \
        for (size_t i = 0; i < len; i++)                    \
            ll_append(ll, many[i]);                         \
    } while (0)


#define ll_append_ll(ll, other) ll_foreach(item, other) ll_append(ll, item->value)


#define ll_shift(ll)                                        \
    ({                                                      \
        assert((ll)->count);                                \
        NodeVal(ll) vhead = REMOVED((ll)->head);            \
                                                            \
        if ((ll)->count == 1) {                             \
            free((ll)->head);                               \
            set_head_tail((ll), NULL);                      \
        } else {                                            \
            (ll)->head = (ll)->head->next;                  \
            if (dll) {                                      \
                free((ll)->head->prev);                     \
                (ll)->head->prev = NULL;                    \
            }                                               \
        }                                                   \
                                                            \
        (ll)->count--;                                      \
        vhead;                                              \
    })


#define ll_remove(ll, index)                                \
    ({                                                      \
        assert((ll)->count > 0);                            \
        assert(index >= 0 && index < (ll)->count);          \
        NodeVal(ll) val;                                    \
                                                            \
        if (index == 0) {                                   \
            val = ll_shift(ll);                             \
        } else if (index == (ll)->count - 1 && dll) {       \
            val = REMOVED((ll)->tail);                      \
            (ll)->tail = (ll)->tail->prev;                  \
            free((ll)->tail->next);                         \
            (ll)->tail->next = NULL;                        \
                                                            \
            (ll)->count--;                                  \
        } else {                                            \
            Node(ll) aux = (ll)->head;                      \
            for (size_t i = 1; i < index; i++)              \
                aux = aux->next;                            \
                                                            \
            if (dll) {                                      \
                aux = aux->next;                            \
                aux->prev->next = aux->next;                \
                aux->next->prev = aux->prev;                \
                                                            \
                val = REMOVED(aux);                         \
                free(aux);                                  \
            } else {                                        \
                Node(ll) removed = aux->next;               \
                                                            \
                aux->next = aux->next->next;                \
                if (aux->next == NULL)                      \
                    (ll)->tail = aux;                       \
                                                            \
                val = REMOVED(removed);                     \
                free(removed);                              \
            }                                               \
            (ll)->count--;                                  \
        }                                                   \
        val;                                                \
    })


#define ll_pop(ll)                                          \
    ({                                                      \
        assert((ll)->count > 0);                            \
        NodeVal(ll) vtail = REMOVED((ll)->tail);            \
                                                            \
        if ((ll)->count == 1) {                             \
            ll_shift(ll);                                   \
        } else if (dll) {                                   \
            (ll)->tail = (ll)->tail->prev;                  \
            free((ll)->tail->next);                         \
            (ll)->tail->next = NULL;                        \
                                                            \
            (ll)->count--;                                  \
        } else {                                            \
            ll_remove(ll, (ll)->count - 1);                 \
        }                                                   \
        vtail;                                              \
    })


#define ll_get(ll, index)                                   \
    ({                                                      \
        assert((ll)->count);                                \
        assert(index >= 0 && index < (ll)->count);          \
        typeof((ll)->head->value) res;                      \
        if (index == (ll)->count - 1) {                     \
            res = (ll)->tail->value;                        \
        } else {                                            \
            Node(ll) aux = (ll)->head;                      \
            for (size_t i = 1; i <= index; i++)             \
                aux = aux->next;                            \
                                                            \
            (res) = aux->value;                             \
        }                                                   \
        res;                                                \
    })
