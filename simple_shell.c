#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

int main() {
    char *command = NULL;
    size_t len = 0;
    ssize_t read;

    pid_t pid;

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
            char *argv[2];
            argv[0] = command;  
            argv[1] = NULL; 

            execve(argv[0], argv, environ);
            perror(command);
            exit(1);
        } else {
            wait(NULL);
        }
    }

    free(command); 
    return 0;
}
