#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

char pattern_yes[] = "yes";
char pattern_no[] = "no";

bool Match_Checking(char string[], char pattern[]);

int main() {
    printf("Do you wont add this app in startup apps? Your ans (yes or no): ");
    char yes_or_no[10];
    scanf_s("%9s", yes_or_no, (unsigned)sizeof(yes_or_no));
    if (Match_Checking(yes_or_no, pattern_yes)) {
        printf("Hello world!\n");
    }

    return 0;
}

bool Match_Checking(char* string, char* pattern) {
    int i, j, k;
    for (i = 0; string[i] != '\0'; i++) {
        for (j = i, k = 0; pattern[j] != '\0' && string[j] == pattern[k]; j++, k++);

        if ((k > 0 && pattern[k] == '\0') && (i >= 0)) {            
             return true;
        }
    }

    return false;
}

// path to startup apps: 
// HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run
// HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
// HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\RunOnce
// HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\RunOnce
