#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int main() {
  FILE *save_file = fopen(SAVE_FILE_PATH, "rb");
  if (!save_file) {
    fprintf(stderr, "ERROR: No File Found at %s\n", SAVE_FILE_PATH);
    exit(1);
  }
  printf("LOG: File Found at %s\n", SAVE_FILE_PATH);

  // Let's get the signature

  return 0;
}