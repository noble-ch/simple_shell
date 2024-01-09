#include "main.h"
#include <stdio.h>

void process_file(char *filename)
{
    char *command;

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    command = (char*)malloc(BUFFER_SIZE * sizeof(char));
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
    char *command;

    command = (char*)malloc(BUFFER_SIZE * sizeof(char));
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