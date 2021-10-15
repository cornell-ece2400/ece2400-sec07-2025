//========================================================================
// selection-sort-int-directed-test.c
//========================================================================
// This file contains the tests for the selection sort function

#include "ece2400-stdlib.h"
#include "selection-sort-int.h"
#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------------------------
// test_case_1_simple
//------------------------------------------------------------------------
// Simple test case for the selection sort function.

void test_case_1_simple()
{
  printf( "\n%s\n", __func__ );
  int a[] = { 11, 7 };
  selection_sort_int( a, 2 );
  ECE2400_CHECK_INT_EQ( a[0], 7  );
  ECE2400_CHECK_INT_EQ( a[1], 11 );
}

//------------------------------------------------------------------------
// test_case_five_element
//------------------------------------------------------------------------
// Simple test case that tests sorting 5 numbers.

void test_case_2_five_element()
{
  printf( "\n%s\n", __func__ );

  int a[]     = { 4, 3, 5, 6, 10 };
  int a_ref[] = { 3, 4, 5, 6, 10 };
  selection_sort_int( a, 5 );
  for ( int i = 0; i < 5; i++ )
    ECE2400_CHECK_INT_EQ( a[i], a_ref[i] );

  int b[]     = { 5, 9, 1, 0, 13 };
  int b_ref[] = { 0, 1, 5, 9, 13 };
  selection_sort_int( b, 5 );
  for ( int i = 0; i < 5; i++ )
    ECE2400_CHECK_INT_EQ( b[i], b_ref[i] );

  int c[]     = { 500, 16, 140, 32, 1000 };
  int c_ref[] = { 16, 32, 140, 500, 1000 };
  selection_sort_int( c, 5 );
  for ( int i = 0; i < 5; i++ )
    ECE2400_CHECK_INT_EQ( c[i], c_ref[i] );
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

// clang-format off
int main( int argc, char** argv )
{
  __n = ( argc == 1 ) ? 0 : atoi( argv[1] );

  if ( ( __n <= 0 ) || ( __n == 1 ) ) test_case_1_simple();
  if ( ( __n <= 0 ) || ( __n == 2 ) ) test_case_2_five_element();

  printf( "\n" );
  return __failed;
}
// clang-format on
