#pragma once

#ifndef REGFUNCTIONS_H
#define REGFUNCTIONS_H

#include <windows.h>

typedef struct {
  HKEY hkey;
  LPCWSTR sub_key;
  LPCWSTR name_value;
  LPCWSTR value;
} regedit_all;

typedef struct {
  wchar_t path[MAX_PATH];
  LPWSTR file_part[MAX_PATH];
  unsigned int path_length;
} path_to_exe;

typedef struct {
  LPWSTR user_name;
  DWORD user_name_size;
} user_name_info;

wchar_t **found_letter_drivers(const DWORD driver_number, unsigned int *length);
LSTATUS regedit_open_key(const HKEY hkey, regedit_all *data);
void regedit_add_to_startup(regedit_all *data, const LSTATUS status);
void free_drivers(wchar_t **drivers_arr, const unsigned int len);
UINT *сheck_for_static_drives(wchar_t **drivers_arr, const unsigned int len);
path_to_exe get_path_to_exe(wchar_t *file_name);
void get_user_name(user_name_info *info);
wchar_t *get_cpu_name(HKEY hkey, regedit_all *data);

#endif // REGFUNCTIONS_H
