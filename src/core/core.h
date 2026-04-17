#ifndef CORE_H
#define CORE_H

#include "../registryFunctions/registryFunctions.h"

typedef enum {
  MAIN,
  ADD_TO_STARTUP,
  DRIVES,
} Screen;

void add_to_startup_screen(regedit_all reg_add);
void swich_user_input(int user_answer, Screen *Current_screen);
void drives_info_screen();

#endif