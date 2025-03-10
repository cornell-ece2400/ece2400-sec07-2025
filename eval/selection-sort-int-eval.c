//========================================================================
// selection-sort-int-eval.c
//========================================================================
// This program evalutes the performance of selection sort by running for
// multiple trials and averaging the elapsed run times.
//

#include "ece2400-stdlib.h"
#include "selection-sort-int.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------
// Input dataset
//------------------------------------------------------------------------

#include "sort.dat"

//------------------------------------------------------------------------
// print_help
//------------------------------------------------------------------------
// Helper function to print the help message.

void print_help() {
  printf(
      "usage: ./selection-sort-int-eval <pattern> <size>\n\n"
      "Evaluation program for selection sort\n\n"
      "positional arguments:\n"
      "  pattern     Pattern of the input array. Available patterns: { urandom, sorted-asc, sorted-desc }\n"
      "  size        Size of the input array. It has to be within (0, 50000].\n");
}

//------------------------------------------------------------------------
// get_arr
//------------------------------------------------------------------------
// Helper function that returns one of three input datasets.

int* get_arr(char* p) {
  if (strcmp(p, "urandom") == 0)
    return arr_urandom;
  if (strcmp(p, "sorted-asc") == 0)
    return arr_sorted_asc;
  if (strcmp(p, "sorted-desc") == 0)
    return arr_sorted_desc;
  return NULL;
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

int main(int argc, char** argv) {
  int  eval_size;
  int* eval_arr;

  // Check command line arguments

  if (argc != 3) {
    printf("Invalid command line arguments!\n\n");
    print_help();
    return 1;
  } else {
    eval_arr = get_arr(argv[1]);

    // Check pattern
    if (eval_arr == NULL) {
      printf("Invalid pattern: %s\n\n", argv[1]);
      print_help();
      return 1;
    }

    eval_size = atoi(argv[2]);

    // Check size
    if (eval_size < 1 || eval_size > arr_size) {
      printf("Invalid size: %d\n\n", eval_size);
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

  int heap_usage;
  int heap_usage_total = 0;

  // Creates buffers for input and reference data

  int* arr_buffer = malloc((size_t) eval_size * sizeof(int));

  // Creates buffers for reference data and use qsort as reference

  int* ref_buffer = malloc((size_t) eval_size * sizeof(int));
  memcpy(ref_buffer, eval_arr, (size_t) eval_size * sizeof(int));
  ece2400_sort(ref_buffer, eval_size);

  printf("Sort with %s dataset of size %d\n", argv[1], eval_size);

  // Timing loop

  for (int i = 0; i < ntrials; i++) {
    // Reset memory counter
    ece2400_mem_reset();

    // Start tracking time
    ece2400_timer_reset();

    // NOTE: here we have to time the memcpy as well. This may add a
    // linear trailing term to the time complexity.
    for (int j = 0; j < nsubtrials; j++) {
      // Copy the input dataset for in-place sort
      memcpy(arr_buffer, eval_arr, (size_t) eval_size * sizeof(int));

      // Run the sort
      selection_sort_int(arr_buffer, eval_size);
    }

    // Stop tracking time
    elapsed = ece2400_timer_get_elapsed();

    // Get heap usage
    heap_usage = ece2400_mem_get_peak();

    // Accumulate result
    elapsed_total += elapsed;
    heap_usage_total += heap_usage;

    printf("Trial %d: elapsed time = %f second, peak heap usage = %d byte\n", i,
           elapsed, heap_usage);
  }

  // Calculate average elapsed time and peak heap usage

  double elapsed_avg    = elapsed_total / ntrials;
  int    heap_usage_avg = heap_usage_total / ntrials;

  printf("Average: elapsed time = %f second, peak heap usage = %d byte\n",
         elapsed_avg, heap_usage_avg);

  // Verify the results

  if (memcmp(arr_buffer, ref_buffer, (size_t) eval_size * sizeof(int)) != 0) {
    printf("Error: Dataset '%s' was not sorted correctly!\n", argv[1]);
    free(arr_buffer);
    free(ref_buffer);
    return 1;
  } else {
    printf("Verfication passed\n");
  }

  free(arr_buffer);
  free(ref_buffer);
  return 0;
}
