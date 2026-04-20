#ifndef CORE_H
#define CORE_H

#include "../registry/registry.h"

typedef enum {
  MAIN,
  ADD_TO_STARTUP,
  DRIVES,
  _SYSTEM_INFO_USER,
} Screen;

void add_to_startup_screen();
void swich_user_input(int user_answer, Screen *Current_screen);
void drives_info_screen();
void system_info_screen();

#endif