//========================================================================
// insertion-sort.h
//========================================================================
// Declarations for insertion sort

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <stdlib.h>

// Helper function

void sorted_insert( int* a, size_t begin, size_t end, int value );

// Sort function

void insertion_sort( int a[], size_t size );

#endif // INSERTION_SORT_H

