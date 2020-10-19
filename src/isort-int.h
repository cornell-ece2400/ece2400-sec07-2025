//========================================================================
// isort_int.h
//========================================================================
// Declarations for insertion sort

#ifndef ISORT_INT_H
#define ISORT_INT_H

#include <stdlib.h>

// Helper function

void sorted_insert( int* a, size_t begin, size_t end, int value );

// Sort function

void isort_int( int a[], size_t size );

#endif // ISORT_INT_H

