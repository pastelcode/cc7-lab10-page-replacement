#ifndef INPUT_H
#define INPUT_H

#define MAX_SEQUENCE_LEN 1024
#define MAX_FRAMES 64

typedef struct {
  int N;
  int reference_length;
  int reference_sequence[MAX_SEQUENCE_LEN];
} InputData;

typedef struct {
  int hits;
  int misses;
} AlgorithmResult;

// Parses CLI args. Exits on error.
InputData parse_input(int argc, char *argv[]);

#endif // INPUT_H
