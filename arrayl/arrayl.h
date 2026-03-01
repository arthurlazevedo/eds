#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define max(a, b) a > b ? a : b


#define da_resize(da, cap)                                                  \
    do {                                                                    \
        size_t isize = sizeof(*(da)->items);                                \
        int* arr = malloc(isize * (cap));                                   \
        memcpy(arr, (da)->items, isize * (da)->count);                      \
        (da)->items = arr;                                                  \
        (da)->capacity = cap;                                               \
    } while (0)


#define da_ensure(da, cap)                                                  \
    do {                                                                    \
        if ((cap) >= (da)->capacity)                                        \
            da_resize((da), max((cap), (da)->capacity * 1.5));              \
    } while (0)


#define da_lshift(da, idx)                                                  \
    do {                                                                    \
        assert((idx) >= 0 && (idx) < (da)->count);                          \
        for (int i = (idx); i < (da)->count; i++)                           \
            (da)->items[i] = (da)->items[i + 1];                            \
        (da)->count--;                                                      \
    } while (0)


#define da_rshift(da, idx)                                                  \
    do {                                                                    \
        assert((idx) >= 0 && (idx) < (da)->count);                          \
        for (int i = (da)->count - 1; i >= (idx); i--)                      \
            (da)->items[i + 1] = (da)->items[i];                            \
        (da)->count++;                                                      \
    } while (0)


#define da_append(da, e)                                                    \
    do {                                                                    \
        da_ensure((da), (da)->count);                                       \
        (da)->items[(da)->count++] = (e);                                   \
    } while (0)


#define da_append_many(da, many, len)                                       \
    do {                                                                    \
        da_ensure((da), (da)->count + (len));                               \
        int msize = sizeof(*(many));                                          \
        memcpy(((da)->items + (da)->count), (many), msize * (len));         \
        (da)->count += len;                                                 \
    } while (0)


#define da_pop(da) (assert((da)->count), (da)->items[--(da)->count])


#define da_last(da) (assert((da)->count), (da)->items[(da)->count - 1])


#define da_add(da, idx, e)                                                  \
    do {                                                                    \
        assert((idx) >= 0 && (idx) <= (da)->count);                         \
        da_ensure((da), (da)->count + 1);                                   \
        da_rshift((da), (idx));                                             \
        (da)->items[(idx)] = (e);                                           \
    } while (0)


#define da_add_unordered(da, idx, e)                                        \
    do {                                                                    \
        assert((idx) >= 0 && (idx) <= (da)->count);                         \
        da_ensure((da), (da)->count + 1);                                   \
        (da)->items[(da)->count++] = (da)->items[(idx)];                    \
        (da)->items[(idx)] = e;                                             \
    } while (0)


#define da_remove(da, idx)                                                  \
    do {                                                                    \
        assert((idx) >= 0 && (idx) < (da)->count);                          \
        da_lshift((da), (idx));                                             \
    } while (0)


#define da_remove_unordered(da, idx)                                        \
    do {                                                                    \
        assert((idx) >= 0 && (idx) < (da)->count);                          \
        (da)->items[(idx)] = da_pop((da));                                  \
    } while (0)
