#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

int main() {
    char command[100];
    pid_t pid;
    char *token;
    char *args[11];
    int arg_count;

    while (1) {
        write(STDOUT_FILENO, "#cisfun$ ", 9);

        fgets(command, 100, stdin);

        if (feof(stdin)) {
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        arg_count = 0;
        token = strtok(command, " ");

        while (token != NULL) {
            args[arg_count++] = token;

            if (arg_count == 10) {
                fprintf(stderr, "Exceeded maximum number of arguments\n");
                exit(1);
            }

            token = strtok(NULL, " ");
        }

        args[arg_count] = NULL;

        pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            execve(args[0], args, environ);
            perror(args[0]);
            exit(1);
        } else {
            wait(NULL);
        }
    }

    return 0;
}
