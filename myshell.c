#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>

void process_input(FILE *stream);

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
		FILE *file;

		file = fopen(argv[1], "r");
		if (file == NULL)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
		process_input(file);
		fclose(file);
	}
	else
	{
		process_input(stdin);
	}

	return (0);
}

/**
 * process_input - Process user input from a specified stream
 * @stream: The input stream
 */

void process_input(FILE *stream)
{
	char *command;
	size_t bufsize;

	command = NULL;
	bufsize = BUFFER_SIZE;

	while (1)
	{
		display_prompt();

		if (custom_getline(&command, &bufsize, stream) == -1)
		{
			printf("\n");
			break;
		}

		if (strlen(command) > 0)
			handle_commands(command);
	}
	free(command);
}
