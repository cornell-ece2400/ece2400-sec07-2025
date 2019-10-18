//========================================================================
// insertion-sort.c
//========================================================================
// Implementation of the insertion sort function
//
//--------------------!!! IMPORTANT NOTE !!!------------------------------
//
// You need to use ece2400_malloc and ece2400_free in your implementation
// in order to get memory usage for eval!
//
//------------------------------------------------------------------------
//

#include <stdio.h>
#include "insertion-sort.h"
#include "ece2400-stdlib.h"

//------------------------------------------------------------------------
// sorted_insert
//------------------------------------------------------------------------
// Insert an element into the proper location to preseve the invariant
// that the given array is always sorted.

void sorted_insert( int* a, size_t begin, size_t end, int value )
{
  //'''' TUTORIAL TASK '''''''''''''''''''''''''''''''''''''''''''''''''''
  // Implement this function
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
  // You can use either a forward (start from begin and iterate to end)
  // or reverse (start from end and iterate to begin) implementation.
}

//------------------------------------------------------------------------
// insertion_sort
//------------------------------------------------------------------------
// Sorts the array with insertion sort.

void insertion_sort( int* a, size_t size )
{
  //'''' TUTORIAL TASK '''''''''''''''''''''''''''''''''''''''''''''''''''
  // Implement this function
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
  // You can use either an out-of-place or an in-place implementation.
}

