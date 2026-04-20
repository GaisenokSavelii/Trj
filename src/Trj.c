#include <Windows.h>
#include <stdio.h>

#include "modules/modules.h"
#include "registry/registry.h"

#pragma comment(lib, "advapi32.lib")

int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

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

      user_name_info user_info;
      get_user_name(&user_info);

      printf("Hello, %ls! \n\n", user_info.user_name);

      printf("Choose what you want to do (type number): \n"
             "1. Show my logical drives; \n"
             "2. Add this application to startup;\n"
             "3. System info;\n");

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
      add_to_startup_screen();
      Current_screen = MAIN;
      break;
    }

    case DRIVES: {
      drives_info_screen();
      Current_screen = MAIN;
      break;
    }

    case _SYSTEM_INFO_USER: {
      system_info_screen();
      Current_screen = MAIN;
      break;
    }
    }
  end:;
  }

  return 0;
}
