#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
/*fonctions prototype*/
void print_env(void);
char **split_string(char *input, char **command);
void free_token_command(char **token);
int check_spaces_tabs(char *input);
void execute_command(char **argv, char **command, char **env);
char *find_command(char *command);
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
ssize_t read_input(char **input, size_t *buf_size);
int check_exit(char **args);
extern char **environ;
#endif
