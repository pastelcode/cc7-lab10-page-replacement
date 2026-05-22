#include "input.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

InputData parse_input(int argc, char *argv[]) {
  InputData data;

  // Validations:

  // Exactly 2 arguments (after program name)
  if (argc != 3) {
    fprintf(stderr, "Usage: ./page_replacement N \"p1 p2 ...\"\n");
    exit(EXIT_FAILURE);
  }

  // N is a valid integer
  char *end_pointer;
  long n_value = strtol(argv[1], &end_pointer, 10);
  if (*end_pointer != '\0' || (n_value == 0 && end_pointer == argv[1])) {
    fprintf(stderr, "Error: N must be an integer.\n");
    exit(EXIT_FAILURE);
  }

  // N >= 1
  if (n_value < 1) {
    fprintf(stderr, "Error: N must be >= 1.\n");
    exit(EXIT_FAILURE);
  }

  // N <= MAX_FRAMES
  if (n_value > MAX_FRAMES) {
    fprintf(stderr, "Error: N must be <= %d.\n", MAX_FRAMES);
    exit(EXIT_FAILURE);
  }

  data.N = (int)n_value;

  // Reference string is not empty (after trimming)
  const char *reference_string = argv[2];
  // Skip leading spaces
  while (*reference_string && isspace((unsigned char)*reference_string)) {
    reference_string++;
  }
  if (*reference_string == '\0') {
    fprintf(stderr, "Error: reference string must not be empty.\n");
    exit(EXIT_FAILURE);
  }

  // Tokenize the reference string and validate each token
  // Make a copy because strtok modifies the string
  char *reference_copy = malloc(strlen(argv[2]) + 1);
  if (!reference_copy) {
    fprintf(stderr, "Error: out of memory.\n");
    exit(EXIT_FAILURE);
  }
  strcpy(reference_copy, argv[2]);

  int reference_length = 0;
  char *token = strtok(reference_copy, " ");

  while (token != NULL) {
    // Each token is a valid non-negative integer
    char *token_end_pointer;
    long page_value = strtol(token, &token_end_pointer, 10);
    if (*token_end_pointer != '\0') {
      fprintf(stderr, "Error: invalid token '%s' in reference string.\n",
              token);
      free(reference_copy);
      exit(EXIT_FAILURE);
    }

    // No negative page IDs
    if (page_value < 0) {
      fprintf(stderr, "Error: page IDs must be >= 0 (got %ld).\n", page_value);
      free(reference_copy);
      exit(EXIT_FAILURE);
    }

    // Sequence length <= MAX_SEQUENCE_LEN
    if (reference_length >= MAX_SEQUENCE_LEN) {
      fprintf(stderr, "Error: reference string too long (max %d).\n",
              MAX_SEQUENCE_LEN);
      free(reference_copy);
      exit(EXIT_FAILURE);
    }

    data.reference_sequence[reference_length] = (int)page_value;
    reference_length++;

    token = strtok(NULL, " ");
  }

  free(reference_copy);

  data.reference_length = reference_length;

  return data;
}
