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
