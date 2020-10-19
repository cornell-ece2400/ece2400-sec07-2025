//========================================================================
// isort-int-eval.c
//========================================================================
// This program evalutes the performance of insertion sort by running for
// multiple trials and averaging the elapsed run times.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isort-int.h"
#include "ece2400-stdlib.h"

//------------------------------------------------------------------------
// Input dataset
//------------------------------------------------------------------------

#include "sort.dat"

//------------------------------------------------------------------------
// print_help
//------------------------------------------------------------------------
// Helper function to print the help message.

void print_help()
{
  printf(
    "usage: ./insertion-sort-eval <pattern> <size>\n\n"
    "Evaluation program for insertion_sort\n\n"
    "positional arguments:\n"
    "  pattern     Pattern of the input array. It can be urandom0, urandom1, urandom2, reversed, or sorted.\n"
    "  size        Size of the input array. It has to be within (0, 50000].\n"
  );
}

//------------------------------------------------------------------------
// find_pattern
//------------------------------------------------------------------------
// Helper function that finds .

int* get_arr( char* p )
{
  if ( strcmp( p, "urandom0" ) == 0 ) return a_urandom0;
  if ( strcmp( p, "urandom1" ) == 0 ) return a_urandom1;
  if ( strcmp( p, "urandom2" ) == 0 ) return a_urandom2;
  if ( strcmp( p, "reversed" ) == 0 ) return a_reversed;
  if ( strcmp( p, "sorted"   ) == 0 ) return a_sorted;
  return NULL;
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

int main( int argc, char** argv )
{
  int  eval_size;
  int* eval_arr;

  // Check command line arguments

  if ( argc != 3 ) {
    printf("Invalid command line arguments!\n\n");
    print_help();
    return 1;
  }
  else {
    eval_arr = get_arr( argv[1] );

    // Check pattern
    if ( eval_arr == NULL ) {
      printf("Invalid pattern: %s\n\n", argv[1] );
      print_help();
      return 1;
    }

    eval_size = atoi( argv[2] );

    // Check size
    if ( eval_size < 1 || eval_size > a_size ) {
      printf("Invalid size: %d\n\n", eval_size );
      print_help();
      return 1;
    }
  }

  // Run many trials so we can average the run times. Within each trial,
  // run enough subtrials so as to avoid precision issues with
  // gettimeofday().

  const int ntrials    = 5;
  const int nsubtrials = 100;

  double elapsed;
  double elapsed_total = 0.0;

  size_t heap_usage;
  size_t heap_usage_total = 0;

  // Creates buffers for input and reference data

  int* a_buffer = malloc( eval_size * sizeof(int) );

  // Creates buffers for reference data and use qsort as reference

  int* ref_buffer = malloc( eval_size * sizeof(int) );
  memcpy( ref_buffer, eval_arr, eval_size * sizeof(int) );
  ece2400_sort( ref_buffer, eval_size );

  printf( "Sort with %s dataset of size %d\n", argv[1], eval_size );

  // Timing loop

  for ( int i = 0; i < ntrials; i++ ) {

    // Reset memory counter
    ece2400_mem_reset();

    // Start tracking time
    ece2400_timer_reset();

    // NOTE: here we have to time the memcpy as well. This may add a
    // linear trailing term to the time complexity.
    for ( int j = 0; j < nsubtrials; j++ ) {

      // Copy the input dataset for in-plcae sort
      memcpy( a_buffer, eval_arr, eval_size * sizeof(int) );

      isort_int( a_buffer, eval_size );
    }

    // Stop tracking time
    elapsed = ece2400_timer_get_elapsed();

    // Get heap usage
    heap_usage = ece2400_mem_get_peak();

    // Accumulate result
    elapsed_total    += elapsed;
    heap_usage_total += heap_usage;

    printf( "Trial %d: elapsed time = %f second, peak heap usage = %zu byte\n",
             i, elapsed, heap_usage );
  }

  // Calculate average elapsed time and peak heap usage

  double elapsed_avg    = elapsed_total    / ntrials;
  size_t heap_usage_avg = heap_usage_total / ntrials;

  printf( "Average: elapsed time = %f second, peak heap usage = %zu byte\n",
          elapsed_avg, heap_usage_avg );

  // Verify the results

  if ( memcmp( a_buffer, ref_buffer, eval_size * sizeof(int) ) != 0 ) {
    printf( "Error: Dataset '%s' was not sorted correctly!\n", argv[1] );
    return 1;
  }
  else{
    printf("Verfication passed\n");
  }

  free( a_buffer );
  free( ref_buffer );
  return 0;
}
