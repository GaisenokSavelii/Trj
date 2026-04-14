#include <windows.h>
#include <stdio.h>

typedef struct
{
    HKEY hkey;
    LPCWSTR sub_key;
    LPCWSTR name_value;
    LPCWSTR value;
} regedit_all;

LSTATUS regedit_set_value(regedit_all *data)
{
    return RegSetValueExW(
        data->hkey,
        data->name_value,
        0,
        REG_SZ,
        (const BYTE *)data->value,
        (DWORD)(((wcslen(data->value) + 1) * sizeof(wchar_t))));
}

LSTATUS regedit_open_key(HKEY hkey, regedit_all *data)
{
    return RegOpenKeyExW(
        hkey,
        data->sub_key,
        0,
        KEY_SET_VALUE,
        &data->hkey);
}

void regedit_add_to_startup(regedit_all *data, LSTATUS status)
{
    switch (status)
    {
    case ERROR_SUCCESS:
    {
        regedit_set_value(data);

        RegCloseKey(data->hkey);
        break;
    }
    case ERROR_ACCESS_DENIED:
    {
        printf("Access denied. Status: %ld\n", status);
        break;
    }
    case ERROR_FILE_NOT_FOUND:
    {
        printf("File not found. Status: %ld\n", status);
        break;
    }
    default:
    {
        printf("Regedit open error: %ld\n", status);
        break;
    }
    }
}

// Converts the result of the GetLogicalDrives function to logical drives.
// Returns a new array with drive names
char **found_letter_drivers(const DWORD driver_number, unsigned int *length)
{
    if (driver_number & 255)
    {
        int Number_of_characters;
        int driver_number_copy = driver_number;

        for (int i = Number_of_characters = 0; i < 32; i++)
        {
            if ((driver_number >> i) & 1)
            {
                Number_of_characters++;
            }
            else if ((driver_number >> i) == 0)
            {
                break;
            }
        }

        char **Character_Array =
            (char **)calloc(Number_of_characters + 1, sizeof(char *));

        for (int i = 0; i < Number_of_characters; i++)
        {
            Character_Array[i] = (char *)calloc(3, sizeof(char));
        }

        int Array_Length;

        for (int index = Array_Length = 0; index < 32; index++)
        {
            if ((driver_number >> index) & 1)
            {
                Character_Array[Array_Length][0] = 'A' + index;
                Character_Array[Array_Length][1] = '\\';
                Array_Length++;
            }
            else if ((driver_number >> index) == 0)
            {
                break;
            }
        }

        *length = Array_Length;
        return Character_Array;
    }

    *length = 0;
    return NULL;
}
