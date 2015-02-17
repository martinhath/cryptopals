#ifndef H_TUPLE
#define H_TUPLE

#include "stddef.h"

typedef struct {
    double weight;
    size_t value;
} Tuple;


/**
 * Sorts an array of Tuples of size n.
 * @param base Base pointer of the array.
 * @param n Size of the array.
 */
void tuplesort(Tuple* base, size_t n);


#endif
