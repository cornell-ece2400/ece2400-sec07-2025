//========================================================================
// isort-int-directed-tests.c
//========================================================================
// This file contains the tests for the insertion sort function

#include <stdio.h>
#include <stdlib.h>

#include "ece2400-stdlib.h"
#include "isort-int.h"

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
  ECE2400_CHECK_ARRAY_INT_EQ( a, ref0, 10 );

  // Insert 4

  sorted_insert( a, 0, size, 4 );
  size += 1;

  int ref1[] = { 2, 3, 4, 4, 6, 8, 10, 0, 0, 0 };
  ECE2400_CHECK_ARRAY_INT_EQ( a, ref1, 10 );

  // Insert 7

  sorted_insert( a, 0, size, 7 );
  size += 1;

  int ref2[] = { 2, 3, 4, 4, 6, 7, 8, 10, 0, 0 };
  ECE2400_CHECK_ARRAY_INT_EQ( a, ref2, 10 );

  // Insert 99

  sorted_insert( a, 0, 8, 99 );
  size += 1;

  int ref3[] = { 2, 3, 4, 4, 6, 7, 8, 10, 99, 0 };
  ECE2400_CHECK_ARRAY_INT_EQ( a, ref3, 10 );
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

  isort_int( a, size );

  ECE2400_CHECK_ARRAY_INT_EQ( a, ref, size );
}

//'''' TUTORIAL TASK '''''''''''''''''''''''''''''''''''''''''''''''''''
// Add more directed tests
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
// Add at least one more test case for both the helper function and the
// insertion sort function.

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

int main( int argc, char** argv )
{
  __n = ( argc == 1 ) ? 0 : atoi( argv[1] );

  if ( ( __n <= 0 ) || ( __n == 1 ) ) test_case_1_helper();
  if ( ( __n <= 0 ) || ( __n == 2 ) ) test_case_2_simple();

  printf( "\n" );
  return __failed;
}
