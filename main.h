#ifndef MAIN_H
#define MAIN_H

#define BUFFER_SIZE 1024;
#define MAX_ARGS 10;

void display_prompt(void);
void handle_errors(const char *message);
char* get_user_input(void);
void execute_command(char* command);

#endif /* MAIN_H */