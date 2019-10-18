//========================================================================
// insertion-sort-directed-tests.c
//========================================================================
// This file contains the tests for the insertion sort function

#include <stdio.h>
#include <stdlib.h>

#include "utst.h"
#include "insertion-sort.h"

//------------------------------------------------------------------------
// test_case_1_helper
//------------------------------------------------------------------------
// Simple test case for the helper function.

void test_case_1_helper()
{
  printf( "\n%s\n", __func__ );

  // Initial array has 10 elements, but only 5 are valid

  size_t size = 5;
  int    a[]  = { 2, 4, 6, 8, 10, 0, 0, 0, 0, 0 };

  // Insert 3

  sorted_insert( a, 0, size, 3 );
  size += 1;

  int ref0[] = { 2, 3, 4, 6, 8, 10, 0, 0, 0, 0 };
  for ( size_t i = 0; i < 10; i++ )
    UTST_ASSERT_INT_EQ( a[i], ref0[i] );

  // Insert 4

  sorted_insert( a, 0, size, 4 );
  size += 1;

  int ref1[] = { 2, 3, 4, 4, 6, 8, 10, 0, 0, 0 };
  for ( size_t i = 0; i < 10; i++ )
    UTST_ASSERT_INT_EQ( a[i], ref1[i] );

  // Insert 7

  sorted_insert( a, 0, size, 7 );
  size += 1;

  int ref2[] = { 2, 3, 4, 4, 6, 7, 8, 10, 0, 0 };
  for ( size_t i = 0; i < 10; i++ )
    UTST_ASSERT_INT_EQ( a[i], ref2[i] );

  // Insert 99

  sorted_insert( a, 0, 8, 99 );
  size += 1;

  int ref3[] = { 2, 3, 4, 4, 6, 7, 8, 10, 99, 0 };
  for ( size_t i = 0; i < 10; i++ )
    UTST_ASSERT_INT_EQ( a[i], ref3[i] );
}

//------------------------------------------------------------------------
// test_case_2_simple
//------------------------------------------------------------------------
// Simple test case for the sort.

void test_case_2_simple()
{
  printf( "\n%s\n", __func__ );

  size_t size  = 5;
  int    a[]   = { 2, 8, 6, 4, 10 };
  int    ref[] = { 2, 4, 6, 8, 10 };

  insertion_sort( a, size );

  for ( size_t i = 0; i < size; i++ )
    UTST_ASSERT_INT_EQ( a[i], ref[i] );
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

int main( int argc, char** argv )
{
  __n = ( argc == 1 ) ? 0 : atoi( argv[1] );

  if ( ( __n == 0 ) || ( __n == 1 ) ) test_case_1_helper();
  if ( ( __n == 0 ) || ( __n == 2 ) ) test_case_2_simple();

  return 0;
}
