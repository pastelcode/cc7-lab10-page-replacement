#include "trace.h"
#include <stdio.h>

static const char *kSeparator =
    "==================================================";

static double compute_hit_rate(int hits, int misses)
{
  int total = hits + misses;
  if (total == 0)
  {
    return 0.0;
  }
  return (double)hits * 100.0 / (double)total;
}

static void build_frames_string(char *buffer, size_t size, int frames[],
                                int N)
{
  size_t offset = 0;

  if (size == 0)
  {
    return;
  }

  int written = snprintf(buffer + offset, size - offset, "[ ");
  if (written < 0 || offset + written >= size)
  {
    buffer[offset] = '\0';
    return;
  }
  offset += written;

  for (int i = 0; i < N; i++)
  {
    if (frames[i] == -1)
    {
      offset += snprintf(buffer + offset, size - offset, "_");
    }
    else
    {
      offset += snprintf(buffer + offset, size - offset, "%d", frames[i]);
    }

    if (i < N - 1)
    {
      offset += snprintf(buffer + offset, size - offset, ", ");
    }
    else
    {
      offset += snprintf(buffer + offset, size - offset, " ");
    }
  }

  snprintf(buffer + offset, size - offset, "]");
}

void print_algorithm_header(const char *algorithm_name, int N)
{
  printf("%s\n", kSeparator);
  printf("%s (N=%d)\n", algorithm_name, N);
  printf("%s\n", kSeparator);
  printf("step  ref   result  frames           victim\n");
  printf("----- ----- ------  ---------------  ------\n");
}

void print_trace_line(int step, int page, int is_hit, int frames[], int N,
                      int victim)
{
  const char *result = is_hit ? "HIT" : "MISS";
  char frames_buffer[16 * MAX_FRAMES + 4];
  char victim_buffer[16];

  build_frames_string(frames_buffer, sizeof(frames_buffer), frames, N);

  if (victim == -1)
  {
    snprintf(victim_buffer, sizeof(victim_buffer), "-");
  }
  else
  {
    snprintf(victim_buffer, sizeof(victim_buffer), "%d", victim);
  }

  printf("%5d %5d %6s  %-15s  %6s\n", step + 1, page, result, frames_buffer, victim_buffer);
}

void print_algorithm_totals(int hits, int misses)
{
  double hit_rate = compute_hit_rate(hits, misses);
  printf("Totals: hits=%d misses=%d, hit rate = %.2f%%\n\n", hits, misses,
         hit_rate);
}

static void print_summary_row(const char *name, AlgorithmResult result)
{
  double hit_rate = compute_hit_rate(result.hits, result.misses);
  printf("%-14s %7d  %7d  %8.2f%%\n", name, result.hits, result.misses,
         hit_rate);
}

void print_comparison_summary(AlgorithmResult fifo, AlgorithmResult min,
                              AlgorithmResult lru,
                              AlgorithmResult clock_result)
{
  printf("%s\n", kSeparator);
  printf("        COMPARISON SUMMARY\n");
  printf("%s\n", kSeparator);
  printf("Algorithm       Hits    Misses  Hit Rate\n");
  printf("-----------  -------  -------  --------\n");
  print_summary_row("FIFO", fifo);
  print_summary_row("MIN", min);
  print_summary_row("LRU", lru);
  print_summary_row("CLOCK", clock_result);
  printf("%s\n", kSeparator);
}
