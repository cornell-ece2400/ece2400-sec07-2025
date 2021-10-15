//========================================================================
// ece2400-stdlib.c
//========================================================================
// Utility functions to support memory and performance profiling.
//
// Note:
//
// DO NOT CHANGE THE FOLLOWING CODE!
//
// Author: Yanghui Ou, Peitian Pan
//   Date: Oct 13, 2020

#include "ece2400-stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

//------------------------------------------------------------------------
// Global variables
//------------------------------------------------------------------------

/* Memory management and timing global variables */

int mem_usage  = 0;
int peak_usage = 0;

struct timeval start_time;
struct timeval end_time;

const double MILLION = 1000000.0;

/* ECE2400_CHECK_* global variables */

// Initial value of __n should be > 0 so that debug info is not suppressed
// in *-adhoc.c files.
int    __n                 = 1;
int    __failed            = 0;
int    __failure_condition = 0;
int    __int_expr0         = 0;
int    __int_expr1         = 0;
double __double_expr0      = 0.0;
double __double_expr1      = 0.0;

//------------------------------------------------------------------------
// ece2400_malloc
//------------------------------------------------------------------------
// Allocate memory of size mem_size. Return a pointer to the newly
// allocated memory or NULL if the allocation fails.

void* ece2400_malloc( size_t mem_size )
{
  void* ptr = malloc( mem_size + sizeof( int ) );

  if ( ptr ) {
    // Update current usage
    mem_usage += (int) mem_size;

    // Update peak usage
    if ( mem_usage > peak_usage )
      peak_usage = mem_usage;
  }
  else
    return NULL;

  ( (int*) ptr )[0] = (int) mem_size;

  return (void*) ( ( (int*) ptr ) + 1 );
}

//------------------------------------------------------------------------
// ece2400_free
//------------------------------------------------------------------------
// Free the memory block that is allocated using ece2400_malloc. According
// to C standard, if ptr is NULL, no action occurs.

void ece2400_free( void* ptr )
{
  if ( ptr ) {
    mem_usage -= ( (int*) ptr )[-1];
    free( ( ( (int*) ptr ) - 1 ) );
  }
}

//------------------------------------------------------------------------
// ece2400_print_array
//------------------------------------------------------------------------
// Prints the contents in an integer array.

void ece2400_print_array( int* a, int size )
{
  if ( size > 0 )
    printf( "%d", a[0] );
  for ( int i = 1; i < size; i++ )
    printf( ", %d", a[i] );
  printf( "\n" );
}

//------------------------------------------------------------------------
// less_than
//------------------------------------------------------------------------
// Comparison function for qsort.

int less_than( const void* a_p, const void* b_p )
{
  int left  = *(const int*) a_p;
  int right = *(const int*) b_p;

  if ( left > 0 && right < 0 )
    return 1;
  else if ( left < 0 && right > 0 )
    return -1;
  else
    return left - right;
}

//------------------------------------------------------------------------
// ece2400_sort
//------------------------------------------------------------------------
// A reference sorting function that sorts an array of integer in
// ascending order.

void ece2400_sort( int* a, int size )
{
  qsort( (void*) a, (size_t) size, sizeof( int ), less_than );
}

//------------------------------------------------------------------------
// ece2400_mem_reset
//------------------------------------------------------------------------

void ece2400_mem_reset()
{
  mem_usage  = 0;
  peak_usage = 0;
}

//------------------------------------------------------------------------
// ece2400_mem_get_usage
//------------------------------------------------------------------------
// Return the amount of heap space that has been allocated so far in a
// program.

int ece2400_mem_get_usage()
{
  return mem_usage;
}

//------------------------------------------------------------------------
// ece2400_mem_get_peak
//------------------------------------------------------------------------
// Return the peak heap usage.

int ece2400_mem_get_peak()
{
  return peak_usage;
}

//------------------------------------------------------------------------
// ece2400_timer_reset
//------------------------------------------------------------------------
// Resets the timer.

void ece2400_timer_reset()
{
  gettimeofday( &start_time, NULL );
}

//------------------------------------------------------------------------
// ece2400_timer_get_elapsed
//------------------------------------------------------------------------
//  Return the elapased time in seconds.

double ece2400_timer_get_elapsed()
{
  gettimeofday( &end_time, NULL );
  double elapsed_secs = (double) ( end_time.tv_sec - start_time.tv_sec );
  double elapsed_usecs = (double) ( end_time.tv_usec - start_time.tv_usec );
  double elapsed_time = elapsed_secs + ( elapsed_usecs / MILLION );
  return elapsed_time;
}

//************************************************************************
// DO NOT DIRECTLY CALL THE FUNCTIONS BELOW!
//************************************************************************
// The functions implemented below are helper functions that should only
// be called in ECE2400_CHECK_* macros.

//------------------------------------------------------------------------
// __ece2400_get_file_name
//------------------------------------------------------------------------
// Return file name extracted from a __FILE__ string.

char* __ece2400_get_file_name( char* full_path )
{
  int len = (int) strlen( full_path );
  int start_pos = 0;

  for ( int i = len - 1; i >= 0; i-- )
    if ( full_path[i] == '/' ) {
      start_pos = i + 1;
      break;
    }

  return full_path + start_pos;
}

//------------------------------------------------------------------------
// __ece2400_fail
//------------------------------------------------------------------------

void __ece2400_fail( char* file, int lineno, char* expr )
{
  file = __ece2400_get_file_name( file );
  if ( __n < 0 )
    printf( "\n" );
  printf( " - [ " RED "FAILED" RESET " ] %s:%d: %s\n", file, lineno,
          expr );
  __failed = 1;
}

//------------------------------------------------------------------------
// __ece2400_check_and_print_uniop
//------------------------------------------------------------------------

void __ece2400_check_and_print_uniop( char* file, int lineno, char* expr )
{
  file = __ece2400_get_file_name( file );
  if ( __failure_condition ) {
    if ( __n < 0 )
      printf( "\n" );
    printf( " - [ " RED "FAILED" RESET " ] %s:%d: %s (%d)\n", file,
            lineno, expr, __int_expr0 );
    __failed = 1;
  }
  else if ( __n > 0 ) {
    printf( " - [ " GREEN "passed" RESET " ] %s:%d: %s (%d)\n", file,
            lineno, expr, __int_expr0 );
  }
  else if ( __n < 0 ) {
    printf( GREEN "." RESET );
  }
}

//------------------------------------------------------------------------
// __ece2400_check_and_print_int_binop
//------------------------------------------------------------------------

void __ece2400_check_and_print_int_binop( char* file, int lineno, char* expr1,
                                          char* expr2 )
{
  file = __ece2400_get_file_name( file );
  if ( __failure_condition ) {
    if ( __n < 0 )
      printf( "\n" );
    printf( " - [ " RED "FAILED" RESET " ] %s:%d: %s != %s (%d != %d)\n",
            file, lineno, expr1, expr2, __int_expr0, __int_expr1 );
    __failed = 1;
  }
  else if ( __n > 0 ) {
    printf( " - [ " GREEN "passed" RESET
            " ] %s:%d: %s == %s (%d == %d)\n",
            file, lineno, expr1, expr2, __int_expr0, __int_expr1 );
  }
  else if ( __n < 0 ) {
    printf( GREEN "." RESET );
  }
}

//------------------------------------------------------------------------
// __ece2400_check_and_print_double_binop
//------------------------------------------------------------------------

void __ece2400_check_and_print_double_binop( char* file, int lineno,
                                             char* expr1, char* expr2 )
{
  file = __ece2400_get_file_name( file );
  if ( __failure_condition ) {
    if ( __n < 0 )
      printf( "\n" );
    printf( " - [ " RED "FAILED" RESET
            " ] %s:%d: %s != %s (%.10e != %.10e)\n",
            file, lineno, expr1, expr2, __double_expr0, __double_expr1 );
    __failed = 1;
  }
  else if ( __n > 0 ) {
    printf( " - [ " GREEN "passed" RESET
            " ] %s:%d: %s == %s (%.10e == %.10e)\n",
            file, lineno, expr1, expr2, __double_expr0, __double_expr1 );
  }
  else if ( __n < 0 ) {
    printf( GREEN "." RESET );
  }
}
