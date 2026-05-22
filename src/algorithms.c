#include "algorithms.h"
#include "trace.h"
#include <stdio.h>

AlgorithmResult run_fifo(const InputData *input) {
  // TODO: Implement by Agent 2
  print_algorithm_header("FIFO", input->N);

  // FIXME: Stub — returns zeros
  AlgorithmResult result = {0, 0};

  print_algorithm_totals(result.hits, result.misses);
  return result;
}

AlgorithmResult run_min(const InputData *input) {
  // TODO: Implement by Agent 2
  print_algorithm_header("MIN", input->N);

  // FIXME: Stub — returns zeros
  AlgorithmResult result = {0, 0};

  print_algorithm_totals(result.hits, result.misses);
  return result;
}

AlgorithmResult run_lru(const InputData *input) {
  // TODO: Implement by Agent 2
  print_algorithm_header("LRU", input->N);

  // FIXME: Stub — returns zeros
  AlgorithmResult result = {0, 0};

  print_algorithm_totals(result.hits, result.misses);
  return result;
}

