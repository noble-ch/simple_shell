#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

int main(int argc, char *argv[]) {
    char *command = NULL;
    size_t len = 0;
    ssize_t read;

    pid_t pid;
    int i;

    while (1) {
        write(STDOUT_FILENO, "#cisfun$ ", 9);

        if ((read = getline(&command, &len, stdin)) == -1) {
            break;
        }

        if (command[read - 1] == '\n') {
            command[read - 1] = '\0';
        }

        pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            char **args = (char **)malloc((argc + 1) * sizeof(char *));

            if (args == NULL) {
                perror("malloc");
                exit(1);
            }

            args[0] = command;

            for (i = 1; i < argc; i++) {
                args[i] = argv[i];
            }

            args[argc] = NULL;

            execve(args[0], args, environ);
            perror(args[0]);
            free(args);
            exit(1);
        } else {
            wait(NULL);
        }
    }

    free(command);
    return 0;
}
