#include "trace.h"
#include <stdio.h>

void print_algorithm_header(const char *algorithm_name, int N) {
  // TODO: Implement by Agent 3
  (void)algorithm_name;
  (void)N;
}

void print_trace_line(int step, int page, int is_hit, int frames[], int N,
                      int victim) {
  // TODO: Implement by Agent 3
  (void)step;
  (void)page;
  (void)is_hit;
  (void)frames;
  (void)N;
  (void)victim;
}

void print_algorithm_totals(int hits, int misses) {
  // TODO: Implement by Agent 3
  (void)hits;
  (void)misses;
}

void print_comparison_summary(AlgorithmResult fifo, AlgorithmResult min,
                              AlgorithmResult lru,
                              AlgorithmResult second_chance) {
  // TODO: Implement by Agent 3
  (void)fifo;
  (void)min;
  (void)lru;
  (void)second_chance;
}
