#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "arrayl.h"

typedef struct {
    int    *items;
    size_t  count;
    size_t  capacity;
} Dynamic_Array;

int main(void)
{
    Dynamic_Array pog = {0};
    
    assert(pog.count == 0);
    da_append(&pog, 1);
    da_append(&pog, 10);
    da_append(&pog, 100);
    da_append(&pog, 1000);
    da_append(&pog, 10000);
    da_append(&pog, 100000);
    da_append(&pog, 1000000);
    assert(pog.count == 7);

    assert(pog.items[0] == 1);
    assert(pog.items[1] == 10);
    assert(pog.items[2] == 100);
    assert(pog.items[3] == 1000);
    assert(pog.items[4] == 10000);
    assert(pog.items[5] == 100000);
    assert(da_last(&pog) == 1000000);

    int tal[] = {1, 2, 3, 4};

    // nota: se eu passasse &tal, isso seria um apontador para o array, logo, 
    // o sizeof(many) consideraria o tamanho do array (16), e não do int (4)
    da_append_many(&pog, tal, 4);
    assert(pog.items[7] == 1);
    assert(pog.items[8] == 2);
    assert(pog.items[9] == 3);
    assert(da_last(&pog) == 4);
    assert(pog.count == 11);

    da_remove(&pog, 0);
    assert(pog.items[0] == 10);
    assert(pog.items[1] == 100);
    assert(da_last(&pog) == 4);
    assert(pog.count == 10);

    da_remove_unordered(&pog, 0);
    assert(pog.items[0] == 4);
    assert(pog.items[1] == 100);
    assert(da_last(&pog) == 3);
    assert(pog.count == 9);

    assert(da_pop(&pog) == 3);
    assert(da_last(&pog) == 2);
    assert(pog.count == 8);

    da_add(&pog, 0, -1);
    assert(pog.items[0] == -1);
    assert(pog.items[1] == 4);
    assert(pog.items[2] == 100);
    assert(da_last(&pog) == 2);

    da_add_unordered(&pog, 0, -10);
    assert(pog.items[0] == -10);
    assert(pog.items[1] == 4);
    assert(da_last(&pog) == -1);

    return 0;
}