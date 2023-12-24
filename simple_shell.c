#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

int main() {
    char command[100];
    pid_t pid;

    while (1) {
        write(STDOUT_FILENO, "#cisfun$ ", 9);

        fgets(command, 100, stdin);

        if (feof(stdin)) {
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            /* Create a modifiable copy of command for argv */
            char *argv[2];
            argv[0] = strdup(command);  
            argv[1] = NULL; 

            execve(argv[0], argv, environ);
            perror(command);
            exit(1);
        } else {
            wait(NULL);
        }
    }

    return 0;
}
