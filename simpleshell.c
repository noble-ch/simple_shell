#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int main(void)
{
    char *command;

    while (1)
    {
        display_prompt();

        command = get_user_input();

        if (command == NULL)
        {
            printf("\n");
            break;
        }
        execute_command(command);
        free(command);
    }
    return (0);
}