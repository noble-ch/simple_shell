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
    if (argc > 2)
    {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 2)
    {
        process_file(argv[1]);
    }
    else
    {
        process_input();
    }
    return (0);
}