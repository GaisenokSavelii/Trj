#include <Windows.h>
#include <stdio.h>

#include "RegeditFunctions/RegFunctions.h"
#include "core/core.h"

#pragma comment(lib, "advapi32.lib")

int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

  path_to_exe path = get_path_to_exe(L"trj.exe");

  regedit_all reg_add = {
      NULL,
      L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
      L"Discard",
      path.path,
  };

  Screen Current_screen = MAIN;

  while (1) {
    system("cls");

    switch (Current_screen) {
    case MAIN: {
      printf("████████╗██████╗      ██╗\n"
             "╚══██╔══╝██╔══██╗     ██║\n"
             "   ██║   ██████╔╝     ██║\n"
             "   ██║   ██╔══██╗██   ██║\n"
             "   ██║   ██║  ██║╚█████╔╝\n"
             "   ╚═╝   ╚═╝  ╚═╝ ╚════╝ \n\n");

      printf("Choose what you want to do: \n"
             "1. Show my logical drives; \n"
             "2. Add this application to startup;\n");

      int user_answer;

      while (scanf_s("%d", &user_answer) == 1) {
        swich_user_input(user_answer, &Current_screen);
        goto end;
      }

      while (scanf_s("%d", &user_answer) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
          ;
        goto end;
      }
      break;
    }

    case ADD_TO_STARTUP: {
      add_to_startup_screen(reg_add);
      Current_screen = MAIN;
      break;
    }

    case DRIVES: {
      drives_info_screen();
      Current_screen = MAIN;
      break;
    }
    }
  end:;
  }

  return 0;
}
