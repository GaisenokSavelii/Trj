#include<windows.h>
#include<stdio.h>

typedef struct {
    HKEY hkey;
    LPCWSTR sub_key;
    LPCWSTR name_value;
    LPCWSTR value;
} regedit_all;

LSTATUS regedit_add_key(regedit_all* data) {
    return RegSetValueExW(
        data->hkey,
        data->name_value,
        0,
        REG_SZ,
        (const BYTE*)data->value,
        (DWORD)((wcslen(data->value) + 1) * sizeof(wchar_t))
    );
}

LSTATUS regedit_open_key(HKEY parent_key, regedit_all* data) {
    return RegOpenKeyExW(
        parent_key,
        data->sub_key,
        0,
        KEY_SET_VALUE,
        &data->hkey
    );
}

void regedit_add_to_startup(regedit_all* data, LSTATUS status) {
    switch (status) {
    case ERROR_SUCCESS: {
        regedit_add_key(data);

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
        printf("Regedit ex open error: %ld\n", status);
        break;
    }
    }
}

// Converts the result of the GetLogicalDrives function to logical drives. 
// Returns a new array with drive names
char* Found_Letter_Drivers(const DWORD driver_number, unsigned int* length) {
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

        char* Character_Array = (char*)malloc((Number_of_characters + 1) * sizeof(char));
        int Array_Length;

        for (int index = Array_Length = 0; index < 32; index++) {
            if ((driver_number >> index) & 1) {
                Character_Array[Array_Length] = 'A' + index;
                Array_Length ++;
            } else if ((driver_number >> index) == 0) {
                break;
            }
        }

        *length = Array_Length;
        Character_Array[Array_Length] = '\0';
        return Character_Array;
    } 
    
    *length = 0;
    return "";
}
