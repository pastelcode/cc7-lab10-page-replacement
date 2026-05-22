#include "algorithms.h"
#include "trace.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

AlgorithmResult run_fifo(const InputData *input) {
  int N = input->N;
  int reference_length = input->reference_length;
  const int *reference_sequence = input->reference_sequence;

  int frames[MAX_FRAMES];
  // Queue for FIFO: circular buffer
  int queue[MAX_FRAMES];
  int queue_head = 0;
  int queue_tail = 0;
  int frame_count = 0;
  int hits = 0;
  int misses = 0;

  // Initialize frames to -1 (empty)
  for (int i = 0; i < N; i++) {
    frames[i] = -1;
  }

  print_algorithm_header("FIFO", N);

  for (int step = 0; step < reference_length; step++) {
    int page = reference_sequence[step];
    int is_hit = 0;
    int victim = -1;

    // Check if page is already in frames
    for (int i = 0; i < N; i++) {
      if (frames[i] == page) {
        is_hit = 1;
        break;
      }
    }

    if (is_hit) {
      hits++;
      // FIFO does not modify the queue on a hit
    } else {
      misses++;

      if (frame_count < N) {
        // Free slot available: load directly
        frames[frame_count] = page;
        queue[queue_tail] = page;
        queue_tail = (queue_tail + 1) % MAX_FRAMES;
        frame_count++;
      } else {
        // All frames full: evict the oldest page
        victim = queue[queue_head];
        queue_head = (queue_head + 1) % MAX_FRAMES;

        // Find victim's slot in frames and replace it
        for (int i = 0; i < N; i++) {
          if (frames[i] == victim) {
            frames[i] = page;
            break;
          }
        }

        // Enqueue the new page
        queue[queue_tail] = page;
        queue_tail = (queue_tail + 1) % MAX_FRAMES;
      }
    }

    print_trace_line(step, page, is_hit, frames, N, victim);
  }

  print_algorithm_totals(hits, misses);

  AlgorithmResult result = {hits, misses};
  return result;
}

AlgorithmResult run_min(const InputData *input) {
  int N = input->N;
  int reference_length = input->reference_length;
  const int *reference_sequence = input->reference_sequence;

  int frames[MAX_FRAMES];
  int frame_count = 0;
  int hits = 0;
  int misses = 0;

  // Initialize frames to -1 (empty)
  for (int i = 0; i < N; i++) {
    frames[i] = -1;
  }

  print_algorithm_header("MIN", N);

  for (int step = 0; step < reference_length; step++) {
    int page = reference_sequence[step];
    int is_hit = 0;
    int victim = -1;

    // Check if page is already in frames
    for (int i = 0; i < N; i++) {
      if (frames[i] == page) {
        is_hit = 1;
        break;
      }
    }

    if (is_hit) {
      hits++;
    } else {
      misses++;

      if (frame_count < N) {
        // Free slot available— load directly
        frames[frame_count] = page;
        frame_count++;
      } else {
        // All frames full — evict the page whose next use is farthest in the
        // future (or never used again). Tie-break: smallest page ID.
        int victim_frame = 0;
        int farthest_next = -1;
        int victim_page = frames[0];

        for (int i = 0; i < N; i++) {
          int p = frames[i];
          int next_use = INT_MAX; // default: never used again

          // Scan forward from the next step to find the first future use
          for (int j = step + 1; j < reference_length; j++) {
            if (reference_sequence[j] == p) {
              next_use = j;
              break;
            }
          }

          // Select page with the largest next_use (farthest in future),
          // tie-breaking by smallest page ID
          int is_first = i == 0;
          int is_farther = next_use > farthest_next;
          int is_tied_and_smaller =
              next_use == farthest_next && p < victim_page;
          if (is_first || is_farther || is_tied_and_smaller) {
            farthest_next = next_use;
            victim_frame = i;
            victim_page = p;
          }
        }

        victim = victim_page;
        frames[victim_frame] = page;
      }
    }

    print_trace_line(step, page, is_hit, frames, N, victim);
  }

  print_algorithm_totals(hits, misses);

  AlgorithmResult result = {hits, misses};
  return result;
}

AlgorithmResult run_lru(const InputData *input) {
  int N = input->N;
  int reference_length = input->reference_length;
  const int *reference_sequence = input->reference_sequence;

  int frames[MAX_FRAMES];
  int frame_count = 0;
  int hits = 0;
  int misses = 0;

  // Initialize frames to -1 (empty)
  for (int i = 0; i < N; i++) {
    frames[i] = -1;
  }

  // Pre-scan to find the maximum page ID for the last_use_time array
  int max_page_id = 0;
  for (int i = 0; i < reference_length; i++) {
    if (reference_sequence[i] > max_page_id) {
      max_page_id = reference_sequence[i];
    }
  }

  // Allocate and initialize last_use_time: -1 means "never used"
  int *last_use_time = malloc((size_t)(max_page_id + 1) * sizeof(int));
  for (int i = 0; i <= max_page_id; i++) {
    last_use_time[i] = -1;
  }

  print_algorithm_header("LRU", N);

  for (int step = 0; step < reference_length; step++) {
    int page = reference_sequence[step];
    int is_hit = 0;
    int victim = -1;

    // Check if page is already in frames
    for (int i = 0; i < N; i++) {
      if (frames[i] == page) {
        is_hit = 1;
        break;
      }
    }

    if (is_hit) {
      hits++;
    } else {
      misses++;

      if (frame_count < N) {
        // Free slot available — load directly
        frames[frame_count] = page;
        frame_count++;
      } else {
        // All frames full: evict the least recently used page.
        // Tie-break: smallest page ID.
        int victim_frame = 0;
        int oldest_time = last_use_time[frames[0]];
        int victim_page = frames[0];

        for (int i = 1; i < N; i++) {
          int p = frames[i];
          if (last_use_time[p] < oldest_time ||
              (last_use_time[p] == oldest_time && p < victim_page)) {
            oldest_time = last_use_time[p];
            victim_frame = i;
            victim_page = p;
          }
        }

        victim = victim_page;
        frames[victim_frame] = page;
      }
    }

    last_use_time[page] = step;

    print_trace_line(step, page, is_hit, frames, N, victim);
  }

  print_algorithm_totals(hits, misses);

  free(last_use_time);

  AlgorithmResult result = {hits, misses};
  return result;
}

// ── Second Chance (stub — Agent 3 will move to its own files) ───────────────

AlgorithmResult run_second_chance(const InputData *input) {
  // TODO: Implement by Agent 3 — currently a stub
  print_algorithm_header("SECOND CHANCE", input->N);

  AlgorithmResult result = {0, 0};

  print_algorithm_totals(result.hits, result.misses);
  return result;
}
