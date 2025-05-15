#include <stdint.h>

// Each Game Save consists of 14 sections each of 4KB each

// The game alternates which region of the save file it writes to each time the
// game is saved.

// The very first time the game is saved it is saved in save block B.

#define SAVE_FILE_PATH "fire-red/Pokemon - Fire Red Version (U) (V1.1).sav"

#define GAME_SAVE_A_OFFSET 0x0000
#define GAME_SAVE_B_OFFSET 0xE000

#define NUM_SECTIONS 14

// Size of each section (4KB)
#define SECTION_SIZE 0x1000

// section data sizes of each individual fields (in bytes)
#define SECTION_DATA_SIZE 3968
#define SECTION_ID_SIZE 2
#define SECTION_CHECKSUM_SIZE 2
#define SECTION_SIGNATURE_SIZE 4
#define SECTION_SAVE_INDEX_SIZE 4

// section offsets
#define SECTION_DATA_OFFSET 0x0000
#define SECTION_ID_OFFSET 0x0FF4
#define SECTION_CHECKSUM_OFFSET 0x0FF6
#define SECTION_SIGNATURE_OFFSET 0x0FF8
#define SECTION_SAVE_INDEX_OFFSET 0x0FFC

#define TRAINER_INFO_SIZE 3884
#define TEAM_ITEMS_SIZE 3968
#define GAME_STATE_SIZE 3968
#define MISC_DATA_SIZE 3968
#define RIVAL_INFO_SIZE 3848
#define PC_BUFFER_SIZE 3968
#define PC_BUFFER_SIZE_I 2000

#define OFFSET_BY_B(OFFSET) (OFFSET + GAME_SAVE_B_OFFSET)

// 14 types of section
typedef enum {
  TRAINER_INFO,
  TEAM_ITEMS,
  GAME_STATE,
  MISC_DATA,
  RIVAL_INFO,
  PC_BUFFER_A,
  PC_BUFFER_B,
  PC_BUFFER_C,
  PC_BUFFER_D,
  PC_BUFFER_E,
  PC_BUFFER_F,
  PC_BUFFER_G,
  PC_BUFFER_H,
  PC_BUFFER_I
} SectionType;

typedef struct {
  uint8_t data[SECTION_DATA_SIZE];
  SectionType type;
  uint16_t section_id;
  uint16_t checksum;
  uint32_t signature;
  uint32_t save_index;
} Section;