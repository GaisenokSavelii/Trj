#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

#pragma comment(lib, "advapi32.lib")

char pattern_yes[] = "yes";
char pattern_no[] = "no";

bool Match_Checking(const char* string, const char* pattern);
int regedit_add_to_startup();

int main() {
    printf("Do you won't add this app in startup apps? Your ans (yes or no): ");
    char yes_or_no[10];
    outerLoop:
    while ((scanf_s("%9s", yes_or_no, (unsigned)sizeof(yes_or_no))) != EOF) {
        if (Match_Checking(yes_or_no, pattern_yes)) {
            regedit_add_to_startup();
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
        for (j = i, k = 0; pattern[k] != '\0' && string[j] == pattern[k]; k++, j++);

        if ((k > 0 && pattern[k] == '\0') && (i >= 0)) {
            return true;
        }
    }

    return false;
}

int regedit_add_to_startup() {
    HKEY hkey;
    LPCSTR subkey = TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
    LSTATUS status = RegOpenKeyEx(HKEY_CURRENT_USER, subkey, 0, KEY_READ, &hkey);

    switch (status) {
        case ERROR_SUCCESS: {
            printf("Regedit open success");
            char name_key = "TestName";
            char data[20] = "TestData\0";
        
            LONG setRes = RegSetValueEx(
                hkey, name_key, 0, REG_SZ, (LPBYTE)data, strlen(data) + 1
            );
        
            RegCloseKey(hkey);
            break;
        }
        case ERROR_ACCESS_DENIED: {
            printf("access denied. Status: %dl\n", status);
            break;
        }
        case ERROR_FILE_NOT_FOUND: {
            printf("File not found. Status: %dl\n", status);
            break;
        }
        default: {
            printf("Regedit ex open error: %ld\n", status);
            break;
        }
    }

    return 0;
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