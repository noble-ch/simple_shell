#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_environment(void)
{
    char **env = environ;

    while (*env != NULL)
    {
        printf("%s\n", *env);
        env++;
    }
}

int check_command_existence(char *command)
{
    char *path_var = getenv("PATH");
    if (path_var == NULL)
    {
        fprintf(stderr, "Error: PATH environment not found\n");
        return (0);
    }
    char *path_copy = strdup(path_var);
    if (path_copy == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return (0);
    }

    char *path = strtok(path_copy, ":");
    char exec_path[PATH_MAX_LEN];

    int command_found = 0;

    while (path != NULL)
    {
        snprintf(exec_path, sizeof(exec_path), "%s/%s", path, command);

        if (access(exec_path, X_OK) == 0)
        {
            printf("Executable found at: %s\n", exec_path);
            command_found = 1;
            break;
        }
        path = strtok(NULL, ":");
    }
    free(path_copy);
    return (command_found);
}

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
    size_t bufsize = 0;
    int c;
    ssize_t len = 0;

    if (lineptr == NULL || n == NULL)
        return (-1);

    if (*lineptr == NULL)
    {
        bufsize = 128;
        *lineptr = (char *)malloc(bufsize * sizeof(char));
        if (*lineptr == NULL)
            return (-1);
        *n = bufsize;
    }

    while ((c = fgetc(stream)) != EOF && c != '\n')
    {
        if (len + 1 >= *n)
        {
            bufsize *= 2;
            char *new_ptr = (char *)realloc(*lineptr, bufsize);
            if (new_ptr == NULL)
                return (-1);
            *lineptr = new_ptr;
            *n = bufsize;
        }
        (*lineptr)[len++] = c;
    }

    if (c == EOF && len == 0)
        return (len);

    (*lineptr)[len] = '\0';
    return (len);
}

void change_directory(const char *new_directory)
{
    char current_directory[BUFFER_SIZE];
    if (getcwd(current_directory, sizeof(current_directory)) == NULL)
    {
        perror("getcwd() error");
    }
    else
    {
        if (new_directory == NULL || strlen(new_directory) == 0)
        {
            new_directory = getenv("HOME");
        }
        if (chdir(new_directory) == 0)
        {
            setenv("PWD", new_directory, 1);
        }
        else
        {
            perror("chdir() error");
        }
    }
}