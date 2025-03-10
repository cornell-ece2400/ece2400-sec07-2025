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

int find_min(int* x, int begin, int end) {
  assert(begin < end);

  int min   = 2147483647;
  int index = -1;
  for (int i = begin; i < end; i++) {
    if (x[i] < min) {
      min   = x[i];
      index = i;
    }
  }
  return index;
}

//------------------------------------------------------------------------
// selection_sort_int
//------------------------------------------------------------------------
// Sorts the array with selection sort

void selection_sort_int(int* x, int n) {
  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Implement this function
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
  // Go through the whole array and track the minimum index. Then swap
  // the minum value with the ith spot. Repeat.
  for (int i = 0; i < n; ++i) {
    int min_idx = find_min(x, i, n);
    int temp    = x[i];
    x[i]        = x[min_idx];
    x[min_idx]  = temp;
  }
}
