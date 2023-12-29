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
    char* args[MAX_ARGS];

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

        if (command[strlen(command) - 1] == '\n')
            command[strlen(command) - 1] == '\0';

        parse_command(command, args);

        if (strcmp(args[0], "exit") == 0)
        {
            printf("Exiting the shell\n");
            break;
        }
        else if(strcmp(args[0], "env") == 0)
        {
            print_environment();
        }

        if (!check_command_existence(args[0]))
        {
            printf("Command not found: %s\n", args[0]);
            continue;
        }
        execute_command(args);
    }
    free(command);
    return (0);
}