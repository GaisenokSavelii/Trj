#include "../utils/Utils.h"
#include "../RegeditFunctions/RegFunctions.h"
#include <stdio.h>
#include <stdbool.h>

char pattern_yes[] = "y";
char pattern_no[] = "n";

typedef enum
{
    MAIN,
    ADD_TO_STARTUP,
    DRIVES,
} Screen;

void add_to_startup(regedit_all reg_add)
{
    while (1)
    {
        printf("Do you wont add this app in startup apps? Your ans (y or n): \n");
        char user_answer[2];

        while (scanf_s("%9s", &user_answer, (unsigned)sizeof(user_answer)) != EOF)
        {
            if (Match_Checking(user_answer, pattern_yes))
            {
                regedit_add_to_startup(
                    &reg_add,
                    regedit_open_key(
                        HKEY_CURRENT_USER,
                        &reg_add));
                break;
            }
            else if (Match_Checking(user_answer, pattern_no))
            {
                break;
            }
            else
            {
                printf("Provide a valid entry\n");
                break;
            }
        }
    }
}

void swich_user_input(int user_answer, Screen *Current_screen)
{
    switch (user_answer)
    {
    case 1:
    {
        *Current_screen = DRIVES;
        break;
    }
    case 2:
    {
        *Current_screen = ADD_TO_STARTUP;
        break;
    }
    default:
    {
        *Current_screen = MAIN;
        break;
    }
    }
}