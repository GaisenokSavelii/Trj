#include <stdio.h>
#include <Windows.h>

#include "RegeditFunctions/RegFunctions.h"
#include "utils/Utils.h"

#pragma comment(lib, "advapi32.lib")

char pattern_yes[] = "yes";
char pattern_no[] = "no";

int main()
{
    DWORD drives_data = GetLogicalDrives();
    unsigned int drives_dataSize;
    found_letter_drivers(drives_data, &drives_dataSize);
    printf("logical drives found: %u\n", drives_dataSize);

    printf("Do you wont add this app in startup apps? Your ans (yes or no): ");
    char yes_or_no[10];
    while ((scanf_s("%9s", yes_or_no, (unsigned)sizeof(yes_or_no))) != EOF)
    {
        regedit_all reg_add = {
            NULL,
            L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
            L"TEST_NAME",
            L"TEST_VALUE",
        };

        if (Match_Checking(yes_or_no, pattern_yes))
        {
            regedit_add_to_startup(
                &reg_add,
                regedit_open_key(
                    HKEY_CURRENT_USER,
                    &reg_add));
            goto end;
        }
        else if (Match_Checking(yes_or_no, pattern_no))
        {
            goto end;
        }
    }

end:
    return 0;
}