#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

char pattern_yes[] = {"yes"};
char pattern_no[] = { "yes" };

int Match_Checking(char string[], char pattern[]);

int main() {
    printf("You wont't add this app in startup apps? Your ans (yes or no): ");
    char yes_or_no[10];
    scanf_s("%9s", yes_or_no, (unsigned)sizeof(yes_or_no));
    if (Match_Checking(yes_or_no, pattern_yes) >= 0) {
        printf("Hello world!\n");
    }

    return 0;
}

int Match_Checking(char string[], char pattern[]) {
    int i, j, k;
    for (i = 0; string[i] != '\0'; i++) {
        for (j = i, k = 0; pattern[j] != '\0' && string[j] == pattern[k]; j++, k++);

        if (k > 0 && pattern[k] == '\0') {
            return i;
        }
    }

    return -1;
}

// path to startup apps: 
// HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run
// HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
// HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\RunOnce
// HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\RunOnce
