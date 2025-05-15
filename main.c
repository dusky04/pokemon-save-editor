#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "main.h"

u_int16_t get_section_checksum(uint8_t *data_ptr) {
  uint32_t sum = 0;
  for (size_t i = 0; i < SECTION_DATA_SIZE; i += 4) {
    // interpret the uint8_t* as uint32_t* and then deference it to get the
    // actual value
    sum += *(uint32_t *)(data_ptr + i);
  }
  return sum + (sum >> 16);
}

int main() {
  FILE *save_file = fopen(SAVE_FILE_PATH, "rb");
  if (!save_file) {
    fprintf(stderr, "ERROR: No File Found at %s\n", SAVE_FILE_PATH);
    exit(1);
  }
  printf("LOG: File Found at %s\n", SAVE_FILE_PATH);

  // Read Game Save B
  // try to get the trainer details
  // fread(void *, unsigned long, unsigned long, FILE *)
  Section sections[NUM_SECTIONS];

  printf("LOG: Reading from Game Save B.\n");
  printf("LOG: Game Save B\n");
  for (int i = 0; i < NUM_SECTIONS; i++) {
    // Direct offset to game data pointed by Save File B
    const long offset = OFFSET_BY_B(GAME_SAVE_A_OFFSET) + (i * SECTION_SIZE);

    // reading the data of a section
    fseek(save_file, offset, SEEK_SET);
    fread(sections[i].data, sizeof(uint8_t), SECTION_DATA_SIZE, save_file);

    // reading the section ID
    fseek(save_file, offset + SECTION_ID_OFFSET, SEEK_SET);
    fread(&sections[i].section_id, sizeof(uint16_t), 1, save_file);

    // reading the checksum
    fseek(save_file, offset + SECTION_CHECKSUM_OFFSET, SEEK_SET);
    fread(&sections[i].checksum, sizeof(uint16_t), 1, save_file);

    uint16_t calculated_checksum = get_section_checksum(sections[i].data);

    // reading the magic signature
    fseek(save_file, offset + SECTION_SIGNATURE_OFFSET, SEEK_SET);
    fread(&sections[i].signature, sizeof(uint32_t), 1, save_file);

    // reading the save index
    fseek(save_file, offset + SECTION_SAVE_INDEX_OFFSET, SEEK_SET);
    fread(&sections[i].save_index, sizeof(u_int32_t), 1, save_file);

    printf("--------------------------------------------------------------\n");
    printf("     (Offset: %lx)\n", offset);
    printf("     Section ID: %x (hex) -> %d (dec)\n", sections[i].section_id,
           sections[i].section_id);
    printf("     Checksum: %x (hex) -> %d (dec)\n", sections[i].checksum,
           sections[i].checksum);
    printf("     Calculated Checksum: %x (hex) -> %d (dec)\n",
           calculated_checksum, calculated_checksum);
    printf("     Signature: %x (hex) -> %d (dec)\n", sections[i].signature,
           sections[i].signature);
    printf("     Save Index: %x (hex) -> %d (dec)\n", sections[i].save_index,
           sections[i].save_index);
  }
  printf("--------------------------------------------------------------\n");

  fclose(save_file);
  return 0;
}