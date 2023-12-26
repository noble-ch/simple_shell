#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
 * The Do's
 * Display a prompt and wait for the user to type a command. A command line always ends with a new line.
 * The prompt is displayed again each time a command has been executed.
 * The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
 * The command lines are made only of one word. No arguments will be passed to programs.
 * If an executable cannot be found, print an error message and display the prompt again.
 * Handle errors.
 * You have to handle the “end of file” condition (Ctrl+D)
 * 
 * The Don'ts
 * use the PATH
 * implement built-ins
 * handle special characters : ", ', `, \, *, &, #
 * be able to move the cursor
 * handle commands with arguments
 * 
*/

int main(void) {
    char *command;
    size_t bufsize = 1024;
    pid_t pid; 

    command = (char *)malloc(bufsize * sizeof(char));

    if (command == NULL) {
        perror("malloc error");
        exit(1);
    }


    while (1) {
        printf("#cisfun$ "); 

        if (getline(&command, &bufsize, stdin) == -1) 
        {
            printf("\n");
            break;
        }

        if (command[strlen(command) - 1] == '\n')
            command[strlen(command) - 1] = '\0';

        pid = fork(); 

        if (pid == -1) {
            perror("fork error");
            exit(1);
        } else if (pid == 0) {
            char **args = (char **)malloc(2 * sizeof(char *)); 

            if (args == NULL) {
                perror("malloc error");
                exit(1);
            }

            args[0] = command; 
            args[1] = NULL;   

            if (execve(args[0], args, NULL) == -1) {
                perror("execve error");
                exit(1);
            }
            free(args); 
        } else {
            wait(NULL);
        }
    }

    free(command); 

    return 0;
}
