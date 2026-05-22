#include "algorithms.h"
#include "clock.h"
#include "input.h"
#include "trace.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  InputData data = parse_input(argc, argv);

  // Print initial header
  printf("Frames: N=%d, Sequence length: %d\n", data.N, data.reference_length);
  printf("Reference sequence: ");
  for (int i = 0; i < data.reference_length; i++) {
    printf("%d", data.reference_sequence[i]);
    if (i < data.reference_length - 1) {
      printf(" ");
    }
  }
  printf("\n\n");

  // Run FIFO
  AlgorithmResult fifo_result = run_fifo(&data);

  // Run MIN (Optimal)
  AlgorithmResult min_result = run_min(&data);

  // Run LRU
  AlgorithmResult lru_result = run_lru(&data);

  // Run Clock
  AlgorithmResult clock_result = run_clock(&data);

  // Print comparison summary
  print_comparison_summary(fifo_result, min_result, lru_result, clock_result);

  return 0;
}
