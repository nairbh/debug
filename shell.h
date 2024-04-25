#ifndef SHELL_H
#define SHELL_H

#define DELIMITER " \t"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <stdarg.h>

/*display_prompt.c*/
void display_prompt(void);

/*exit_function.c*/
int _atoi(char *s);
void exitt(char **arv);

/*exec_com.c*/
int custom_execlp(const char *file, const char *arg0, ...);
void execute_command(const char *command);

/*exit_function.c*/
int _atoi(char *s);
void exitt(char **arv);

/*user_input.c*/
void user_input(char *command, size_t size);
void read_command(char *command, size_t size);
void sigint_handler(int signum);

#endif /* SHELL_H */
