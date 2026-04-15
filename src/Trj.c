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
    wchar_t **Character_Array = found_letter_drivers(drives_data, &drives_dataSize);

    printf("logical drives found: %u\n", drives_dataSize);

    UINT *Static_Arrays = сheck_for_static_disks(Character_Array, drives_dataSize);

    path_to_exe path = get_path_to_exe(L"trj.exe");

    printf("Do you wont add this app in startup apps? Your ans (yes or no): ");
    char yes_or_no[10];
    while ((scanf_s("%9s", yes_or_no, (unsigned)sizeof(yes_or_no))) != EOF)
    {
        regedit_all reg_add = {
            NULL,
            L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
            L"Discard",
            path.path,
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
    free_drivers(Character_Array, drives_dataSize);
    return 0;
}
