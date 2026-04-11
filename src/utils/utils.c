#include <stdbool.h>

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