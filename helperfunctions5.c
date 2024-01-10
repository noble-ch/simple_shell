#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *command;
size_t bufsize = BUFFER_SIZE;

void process_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    command = (char *)malloc(BUFFER_SIZE * sizeof(char));
    if (command == NULL)
    {
        handle_errors("malloc error");
        exit(EXIT_FAILURE);
    }

    while (custom_getline(&command, &bufsize, file) == -1)
    {
        if (strlen(command) > 0)
            handle_commands(command);
    }
    free(command);
    fclose(file);
}

void process_input()
{
    command = (char *)malloc(BUFFER_SIZE * sizeof(char));
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
}