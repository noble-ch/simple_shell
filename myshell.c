#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>

int main(void)
{
    char *command;
    size_t bufsize = BUFFER_SIZE;

    command = (char*)malloc(bufsize * sizeof(char));

    if (command == NULL)
    {
        handle_errors("malloc error");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        display_prompt();

        if (custom_getline(&command, &bufsize, stdin) == -1)
        {
            printf("\n");
            break;
        }

        if (strlen(command) == 0)
            continue;

        handle_commands(command);
    }
    free(command);
    return (0);
}