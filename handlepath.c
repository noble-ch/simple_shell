#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

#define MAX_ARGS 10
#define MAX_PATHS 100

int main(int argc, char *argv[]) {
    char command[100];
    pid_t pid;
    int i;

    char *paths[MAX_PATHS];
    char *token;
    int path_count = 0;

    int command_found = 0;

    while (1) {
        write(STDOUT_FILENO, ":) ", 3);

        fgets(command, 100, stdin);

        if (feof(stdin)) {
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        path_count = 0;
        token = strtok(getenv("PATH"), ":");
        
        while (token != NULL && path_count < MAX_PATHS) {
            paths[path_count++] = token;
            token = strtok(NULL, ":");
        }

        command_found = 0;

        for (i = 0; i < path_count; i++) {
            char path_command[200];
            snprintf(path_command, sizeof(path_command), "%s/%s", paths[i], command);

            if (access(path_command, X_OK) == 0) {
                command_found = 1;
                pid = fork();

                if (pid < 0) {
                    perror("fork");
                    exit(1);
                } else if (pid == 0) {
                    char **args = (char **)malloc((argc + 1) * sizeof(char *)); /* Allocate memory for args */

                    if (args == NULL) {
                        perror("malloc");
                        exit(1);
                    }

                    args[0] = path_command; /* First argument is the command itself */

                    /* Copy the rest of the arguments */
                    for (i = 1; i < argc; i++) {
                        args[i] = argv[i];
                    }

                    args[argc] = NULL; /* NULL-terminate the args array */

                    execve(args[0], args, environ);
                    perror(args[0]);
                    free(args); /* Free the dynamically allocated memory */
                    exit(1);
                } else {
                    wait(NULL);
                    break;
                }
            }
        }

        if (!command_found) {
            fprintf(stderr, "%s: command not found\n", command);
        }
    }

    return 0;
}
