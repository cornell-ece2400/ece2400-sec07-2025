//========================================================================
// selection-sort-int-adhoc.c
//========================================================================

#include "ece2400-stdlib.h"
#include "selection-sort-int.h"
#include <stdio.h>

int main()
{
  int size = 4;
  int a[]  = {19, 95, 4, 23};

  // Print out array before

  printf( "Before sorting: " );

  ece2400_print_array( a, size );

  // Call helper

  int min_idx = find_min( a, 0, size );

  // Print out index of minimum value

  printf( "minimum index: %d\n", min_idx );

  return 0;
}
