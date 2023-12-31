#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 10 

void parse_command(char *command, char **args) {
    char *token;
    int index = 0;

    token = strtok(command, " ");

    while (token != NULL && index < MAX_ARGS - 1) {
        args[index++] = token; 
        token = strtok(NULL, " ");
    }
    args[index] = NULL;
}

int main(void) {
    char *command;
    size_t bufsize = 1024;
    pid_t pid;
    char *args[MAX_ARGS];

    command = (char *)malloc(bufsize * sizeof(char));

    if (command == NULL) {
        perror("malloc error");
        exit(1);
    }

    while (1) {
        printf("#cisfun$ ");

        if (getline(&command, &bufsize, stdin) == -1) {
            printf("\n");
            break;
        }

        if (command[strlen(command) - 1] == '\n')
            command[strlen(command) - 1] = '\0';

        parse_command(command, args); 

        pid = fork();

        if (pid == -1) {
            perror("fork error");
            exit(1);
        } else if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror("execvp error");
                exit(1);
            }
        } else {
            wait(NULL);
        }
    }

    free(command);

    return 0;
}
