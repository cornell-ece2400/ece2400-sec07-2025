//========================================================================
// insertion-sort-adhoc.c
//========================================================================

#include <stdio.h>
#include <stdlib.h>

#include "insertion-sort.h"
#include "utils.h"

int main() {

  size_t size  = 5;
  // int    a[]   = { 2, 4, 6, 8, 10, 0, 0, 0, 0, 0 };
  int    a[]   = { 2, 8, 6, 4, 10, 0, 0, 0, 0, 0 };

  // Print out array before

  printf( "Before: " );

  for ( size_t i = 0; i < size; i++ )
    printf( "%d ", a[i] );

  printf( "\n" );

  // Call function to test. Initially this is sorted_insert, but you can
  // change this to be insertion_sort later if you want.

  // sorted_insert( a, 0, 5, 7 );
  // size += 1;

  insertion_sort( a, 5 );

  // Print out arr after

  printf( "After:  " );

  for ( size_t i = 0; i < size; i++ )
    printf( "%d ", a[i] );

  printf( "\n" );

  return 0;
}

