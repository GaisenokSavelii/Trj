#include "./modules.h"
#include "../registry/registry.h"
#include "../system/system.h"
#include "../utils/utils.h"
#include "./modules.h"
#include <conio.h>
#include <corecrt_wconio.h>
#include <minwindef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysinfoapi.h>
#include <wchar.h>
#include <winnt.h>
#include <winreg.h>

char pattern_yes[] = "y";
char pattern_no[] = "n";

void add_to_startup_screen() {
  printf("--- ADDING APPLICATION TO STARTUP ---\n\n");
  printf("Do you wont add this app in startup apps? Your ans (y or n): \n");
  char user_answer[2];

  while (scanf_s("%9s", &user_answer, (unsigned)sizeof(user_answer)) != EOF) {
    if (Match_Checking(user_answer, pattern_yes)) {
      path_to_exe path = get_path_to_exe(L"trj.exe");

      regedit_all reg_add = {
          NULL,
          L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
          L"Trj",
          path.path,
      };

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

  press_any_key();

  free_drivers(Character_Array, drives_dataSize);
  free(Static_Arrays);
}

void system_info_screen() {
  printf("--- SYSTEM INFO ---\n\n");

  regedit_all get_user_cpu = {
      NULL, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
      L"ProcessorNameString", NULL};

  SYSTEM_INFO system_info;
  GetSystemInfo(&system_info);

  SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *x = get_logical_processors_info();

  wchar_t *cpu_name = get_cpu_name(HKEY_LOCAL_MACHINE, &get_user_cpu);
  wchar_t *arch = switch_cpu_architecture(system_info);

  printf("CPU: %ls,\n\n", cpu_name);
  printf("Architecture: %ls,\n\n", arch);
  printf("page size: %lu\n\n", system_info.dwPageSize);

  press_any_key();

  free(cpu_name);
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
  case 3: {
    *Current_screen = _SYSTEM_INFO_USER;
    break;
  }
  default: {
    *Current_screen = MAIN;
    break;
  }
  }
}