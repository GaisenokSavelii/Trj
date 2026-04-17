#include "../RegeditFunctions/RegFunctions.h"
#include "../utils/Utils.h"
#include <conio.h>
#include <stdbool.h>
#include <stdio.h>


char pattern_yes[] = "y";
char pattern_no[] = "n";

typedef enum {
  MAIN,
  ADD_TO_STARTUP,
  DRIVES,
} Screen;

void add_to_startup_screen(regedit_all reg_add) {
  printf("Do you wont add this app in startup apps? Your ans (y or n): \n");
  char user_answer[2];

  while (scanf_s("%9s", &user_answer, (unsigned)sizeof(user_answer)) != EOF) {
    if (Match_Checking(user_answer, pattern_yes)) {
      regedit_add_to_startup(&reg_add,
                             regedit_open_key(HKEY_CURRENT_USER, &reg_add));
      break;
    } else if (Match_Checking(user_answer, pattern_no)) {
      break;
    } else {
      printf("Provide a valid entry\n");
      break;
    }
  }
}

void drives_info_screen() {
  DWORD drives_data = GetLogicalDrives();
  unsigned int drives_dataSize;
  wchar_t **Character_Array =
      found_letter_drivers(drives_data, &drives_dataSize);

  UINT *Static_Arrays =
      сheck_for_static_drives(Character_Array, drives_dataSize);

  printf("--- DRIVES INFORMATION ---\n\n");

  for (int i = 0; i < drives_dataSize; i++) {
    printf("%ls", Character_Array[i]);

    switch (Static_Arrays[i]) {
    case DRIVE_RAMDISK: {
      printf("- The drive is a RAM disk.\n\n");
    }
    case DRIVE_CDROM: {
      printf("- The drive is a CD-ROM drive.\n\n");
    }
    case DRIVE_REMOTE: {
      printf("- The drive is a remote (network) drive.\n\n");
    }
    case DRIVE_FIXED: {
      printf("- is FIXED (non removable) drive.\n\n");
      break;
    }
    case DRIVE_REMOVABLE: {
      printf("- is removable drive.\n\n");
      break;
    }
    case DRIVE_NO_ROOT_DIR: {
      printf("- The root path is invalid.\n");
    }
    case DRIVE_UNKNOWN: {
      printf("- The drive type cannot be determined.\n");
    }
    }
  }

  printf("press any key...");
  _getch();

  free_drivers(Character_Array, drives_dataSize);
  free(Static_Arrays);
}

void swich_user_input(int user_answer, Screen *Current_screen) {
  switch (user_answer) {
  case 1: {
    *Current_screen = DRIVES;
    break;
  }
  case 2: {
    *Current_screen = ADD_TO_STARTUP;
    break;
  }
  default: {
    *Current_screen = MAIN;
    break;
  }
  }
}