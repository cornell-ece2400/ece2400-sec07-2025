//========================================================================
// isort-int-adhoc.c
//========================================================================

#include <stdio.h>
#include <stdlib.h>

#include "isort-int.h"

int main() {

  size_t a_size = 5;
  int    a[]    = { 2, 4, 6, 8, 10, 0, 0, 0, 0, 0 };

  // Print out array before

  printf( "Before: " );

  for ( size_t i = 0; i < a_size; i++ )
    printf( "%d ", a[i] );

  printf( "\n" );

  // Quick ad-hoc test for sorted insert

  sorted_insert( a, 0, 5, 7 );
  a_size += 1;

  // Print out array after

  printf( "After:  " );

  for ( size_t i = 0; i < a_size; i++ )
    printf( "%d ", a[i] );

  printf( "\n" );

  return 0;
}

