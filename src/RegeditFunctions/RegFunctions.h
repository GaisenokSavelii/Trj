#pragma once

#ifndef REGFUNCTIONS_H
#define REGFUNCTIONS_H

#include <windows.h>

typedef struct
{
    HKEY hkey;
    LPCWSTR sub_key;
    LPCWSTR name_value;
    LPCWSTR value;
} regedit_all;

LSTATUS regedit_add_key(regedit_all *data);
char **found_letter_drivers(const DWORD driver_number, unsigned int *length);
LSTATUS regedit_open_key(HKEY parent_key, regedit_all *data);
void regedit_add_to_startup(regedit_all *data, LSTATUS status);
void free_drivers(char **drivers_arr, unsigned int len);

#endif
