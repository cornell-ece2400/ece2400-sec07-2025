//========================================================================
// selection-sort-int-helper-test.c
//========================================================================
// This file contains the whitebox tests for the selection sort
// implementation
// NOTE: there will be no staff tests released for the helper functions

#include "ece2400-stdlib.h"
#include "selection-sort-int.h"
#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------------------------
// test_case_1_simple
//------------------------------------------------------------------------
// Simple test case for the helper function.

void test_case_1_simple()
{
  printf( "\n%s\n", __func__ );
  int a[] = { 11, 7, 20, 0 };
  ECE2400_CHECK_INT_EQ( find_min( a, 0, 4 ), 3 );
  ECE2400_CHECK_INT_EQ( find_min( a, 0, 3 ), 1 );
  ECE2400_CHECK_INT_EQ( find_min( a, 0, 2 ), 1 );
  ECE2400_CHECK_INT_EQ( find_min( a, 0, 1 ), 0 );
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

// clang-format off
int main( int argc, char** argv )
{
  __n = ( argc == 1 ) ? 0 : atoi( argv[1] );

  if ( ( __n <= 0 ) || ( __n == 1 ) ) test_case_1_simple();

  printf( "\n" );
  return __failed;
}
// clang-format on
