#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>

/**
 * main - Entry point for the shell program
 * @argc: The number of command line arguments
 * @argv: An array of command-line strings.
 * 
 * Description: The main function of the shell program. It reads
 * commands from either a file or standard input, processes the
 * commands, and executes them. If a file name is provided as a
 * command-line argument, the program reads commands from the file;
 * otherwise, it reads commands from standard input.
 * 
 * Return: Always returns 0 to indicate successful execution/
*/

int main(int argc, char *argv[])
{
    char *command;
    size_t bufsize;

    bufsize = BUFFER_SIZE;
    if (argc > 2)
    {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 2)
    {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        command = (char*)malloc(bufsize * sizeof(char));
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
        return (0);
    }

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