#include "algorithms.h"
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

  // Run Second Chance (Clock)
  AlgorithmResult sc_result = run_second_chance(&data);

  // Print comparison summary
  print_comparison_summary(fifo_result, min_result, lru_result, sc_result);

  return 0;
}
