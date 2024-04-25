#ifndef SIMPLE_SHELL_H_
#define SIMPLE_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void display_prompt(void);
void interactive_mode(void);
void non_interactive_mode(void);
int run_command(char *input);

#endif /*SIMPLE_SHELL_H_*/
