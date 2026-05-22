#include "clock.h"
#include "trace.h"

typedef struct {
  int page;
  int ref;
} ClockFrame;

AlgorithmResult run_clock(const InputData *input) {
  AlgorithmResult result = {0, 0};
  int frame_count = 0;
  int clock_hand = 0;
  ClockFrame clock_frames[MAX_FRAMES];

  for (int i = 0; i < input->N; i++) {
    clock_frames[i].page = -1;
    clock_frames[i].ref = 0;
  }

  print_algorithm_header("CLOCK", input->N);

  for (int step = 0; step < input->reference_length; step++) {
    int page = input->reference_sequence[step];
    int victim = -1;
    int is_hit = 0;
    int hit_index = -1;

    // Check for hit
    for (int i = 0; i < input->N; i++) {
      if (clock_frames[i].page == page) {
        hit_index = i;
        break;
      }
    }

    if (hit_index != -1) {
      is_hit = 1;
      result.hits++;
      clock_frames[hit_index].ref = 1;
    } else {
      result.misses++;
      // If there's still space, add the page directly
      if (frame_count < input->N) {
        for (int i = 0; i < input->N; i++) {
          if (clock_frames[i].page == -1) {
            clock_frames[i].page = page;
            clock_frames[i].ref = 1;
            frame_count++;
            break;
          }
        }
      } else {
        // Evict a page using the clock algorithm
        while (1) {
          if (clock_frames[clock_hand].ref == 0) {
            victim = clock_frames[clock_hand].page;
            clock_frames[clock_hand].page = page;
            clock_frames[clock_hand].ref = 1;
            clock_hand = (clock_hand + 1) % input->N;
            break;
          }
          // Give a second chance
          clock_frames[clock_hand].ref = 0;
          clock_hand = (clock_hand + 1) % input->N;
        }
      }
    }

    int frame_pages[MAX_FRAMES];
    for (int i = 0; i < input->N; i++) {
      frame_pages[i] = clock_frames[i].page;
    }

    print_trace_line(step, page, is_hit, frame_pages, input->N, victim);
  }

  print_algorithm_totals(result.hits, result.misses);
  return result;
}
