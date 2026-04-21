#ifndef SYSTEM_H
#define SYSTEM_H

#include <Windows.h>

SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *get_logical_processors_info();
wchar_t *switch_cpu_architecture(SYSTEM_INFO system_info);

#endif