#include "tuple.h"

#include <stdlib.h>

static int tuple_cmp(const void *tu1, const void *tu2){
    Tuple *t1 = (Tuple*) tu1;
    Tuple *t2 = (Tuple*) tu2;
    return t1->weight > t2->weight;
}

void tuplesort(Tuple *base, size_t size){
    qsort(base, size, sizeof(Tuple), tuple_cmp);
}
