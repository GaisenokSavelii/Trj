#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

#pragma comment(lib, "advapi32.lib")

char pattern_yes[] = "yes";
char pattern_no[] = "no";

typedef struct {
    HKEY hkey;
    LPCWSTR sub_key;
    LPCWSTR name_value;
    LPCWSTR value;
} regedit_all;

bool Match_Checking(const char* string, const char* pattern);
inline static void regedit_add_to_startup(regedit_all* data, LSTATUS status);
LSTATUS regedit_open_key(HKEY parent_key, regedit_all* data);

int main() {
    printf("Do you won't add this app in startup apps? Your ans (yes or no): ");
    char yes_or_no[10];
    while ((scanf_s("%9s", yes_or_no, (unsigned)sizeof(yes_or_no))) != EOF) {
        regedit_all reg_add = {
            NULL,
            L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
            L"TEST_NAME",
            L"TEST_VALUE",
        };

        if (Match_Checking(yes_or_no, pattern_yes)) {
            regedit_add_to_startup(
                &reg_add,
                regedit_open_key(
                    HKEY_CURRENT_USER,
                    &reg_add
                )
            );
            goto end;
        }
        else if (Match_Checking(yes_or_no, pattern_no)) {
            goto end;
        }
    }

end:
    return 0;
}

bool Match_Checking(const char* string, const char* pattern) {
    int i, j, k;

    for (i = 0; string[i] != '\0'; i++) {
        for (
            j = i, k = 0;
            pattern[k] != '\0' && string[j] == pattern[k];
            k++, j++
            );

        if ((k > 0 && pattern[k] == '\0') && (i >= 0)) {
            return true;
        }
    }

    return false;
}

LSTATUS regedit_open_key(HKEY parent_key, regedit_all *data) {
    return RegOpenKeyEx(
        parent_key,
        data->sub_key,
        0,
        KEY_SET_VALUE,
        &data->hkey
    );
}

inline static void regedit_add_to_startup(regedit_all* data, LSTATUS status) {
    switch (status) {
    case ERROR_SUCCESS: {
        LONG RegAddValue = RegSetValueEx(
            data->hkey,
            data->name_value,
            0,
            REG_SZ,
            (const BYTE*) data->value,
            (DWORD) ((wcslen(data->value) + 1) * sizeof(wchar_t))
        );

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

// path to startup apps: 
// HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run
// HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
// HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\RunOnce
// HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\RunOnce
// RegOpenKeyEx: Открывает существующий раздел реестра.
// RegCreateKeyEx: Создает новый раздел или открывает существующий.
// RegSetValueEx : Устанавливает значение(данные) для указанного параметра.
// RegQueryValueEx : Считывает данные из параметра реестра.
// RegCloseKey : Закрывает дескриптор раздела после завершения работы