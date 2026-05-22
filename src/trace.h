#ifndef TRACE_H
#define TRACE_H

#include "input.h"

void print_algorithm_header(const char *algorithm_name, int N);
void print_trace_line(int step, int page, int is_hit, int frames[], int N,
                      int victim);
void print_algorithm_totals(int hits, int misses);
void print_comparison_summary(AlgorithmResult fifo, AlgorithmResult min,
                              AlgorithmResult lru,
                              AlgorithmResult clock_result);

#endif // TRACE_H
