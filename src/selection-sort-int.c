//========================================================================
// selection-sort-int.c
//========================================================================
// Implementation of the selection sort function
//
//--------------------!!! IMPORTANT NOTE !!!------------------------------
//
// You need to use ece2400_malloc and ece2400_free in your implementation
// in order to get memory usage for eval!
//
//------------------------------------------------------------------------
//

#include "selection-sort-int.h"
#include <assert.h>

//------------------------------------------------------------------------
// find_min
//------------------------------------------------------------------------
// find the index of the minimum number in the array.

int find_min( int* a, int begin, int end )
{
  assert( begin < end );

  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Implement this function
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

  return 0;
}

//------------------------------------------------------------------------
// selection_sort_int
//------------------------------------------------------------------------
// Sorts the array with selection sort

void selection_sort_int( int* a, int size )
{
  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Implement this function
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
  // Go through the whole array and track the minimum index. Then swap
  // the minum value with the ith spot. Repeat.
}

