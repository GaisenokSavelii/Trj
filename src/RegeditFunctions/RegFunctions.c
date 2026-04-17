#include <Windows.h>
#include <stdio.h>

typedef struct {
  HKEY hkey;
  LPCWSTR sub_key;
  LPCWSTR name_value;
  LPCWSTR value;
} regedit_all;

LSTATUS regedit_set_value(regedit_all *data) {
  return RegSetValueExW(data->hkey, data->name_value, 0, REG_SZ,
                        (const BYTE *)data->value,
                        (DWORD)(((wcslen(data->value) + 1) * sizeof(wchar_t))));
}

LSTATUS regedit_open_key(const HKEY hkey, regedit_all *data) {
  return RegOpenKeyExW(hkey, data->sub_key, 0, KEY_SET_VALUE, &data->hkey);
}

void regedit_add_to_startup(regedit_all *data, const LSTATUS status) {
  switch (status) {
  case ERROR_SUCCESS: {
    regedit_set_value(data);

    RegCloseKey(data->hkey);
    break;
  }
  case ERROR_ACCESS_DENIED: {
    printf("Access denied. Status: %ld\n", status);
    break;
  }
  case ERROR_FILE_NOT_FOUND: {
    printf("File not found. Status: %ld\n", status);
    break;
  }
  default: {
    printf("Regedit open error: %ld\n", status);
    break;
  }
  }
}

// Converts the result of the GetLogicalDrives function to logical drives.
// Returns a new array with drive names
wchar_t **found_letter_drivers(const DWORD driver_number,
                               unsigned int *length) {
  if (driver_number & 255) {
    int Number_of_characters;
    int driver_number_copy = driver_number;

    for (int i = Number_of_characters = 0; i < 32; i++) {
      if ((driver_number >> i) & 1) {
        Number_of_characters++;
      } else if ((driver_number >> i) == 0) {
        break;
      }
    }

    wchar_t **Character_Array =
        (wchar_t **)calloc(Number_of_characters + 1, sizeof(wchar_t *));

    for (int i = 0; i < Number_of_characters; i++) {
      Character_Array[i] = (wchar_t *)calloc(5, sizeof(wchar_t));
    }

    int Array_Length;

    for (int index = Array_Length = 0; index < 32; index++) {
      if ((driver_number >> index) & 1) {
        Character_Array[Array_Length][0] = L'A' + index;
        Character_Array[Array_Length][1] = L':';
        Character_Array[Array_Length][2] = L'\\';
        Character_Array[Array_Length][3] = L'\\';
        Array_Length++;
      } else if ((driver_number >> index) == 0) {
        break;
      }
    }

    *length = Array_Length;
    return Character_Array;
  }

  *length = 0;
  return NULL;
}

void free_drivers(wchar_t **drivers_arr, const unsigned int len) {
  if (!drivers_arr)
    return;

  for (unsigned int i = 0; i < len; i++) {
    free(drivers_arr[i]);
  }

  free(drivers_arr);
}

UINT *сheck_for_static_drives(const wchar_t **drivers_arr,
                              const unsigned int len) {
  UINT *flag_array = (UINT *)calloc(len, sizeof(UINT));

  for (int i = 0; i < len; i++) {
    flag_array[i] = GetDriveTypeW(drivers_arr[i]);
  }

  return flag_array;
}

typedef struct {
  wchar_t path[MAX_PATH];
  LPWSTR file_part;
  unsigned int path_length;
} path_to_exe;

path_to_exe get_path_to_exe(wchar_t *file_name) {
  path_to_exe response;
  DWORD length_path_to_exe =
      GetFullPathNameW(file_name, MAX_PATH, response.path, &response.file_part);
  if (length_path_to_exe == 0) {
    return response;
  } else {
    response.path_length = length_path_to_exe;
    return response;
  }
}