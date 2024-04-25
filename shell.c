#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define COMMAND_SIZE 128

char **parse_args(char *command);
void execute_command(char **args);
int read_command(char *command, size_t size);
void display_prompt(void);
void sigint_handler(int unused);

int main(void)
{
    char command[COMMAND_SIZE];
    char **args;
    signal(SIGINT, sigint_handler);

    while (1)
    {
        display_prompt();
        read_command(command, sizeof(command));

        if (strcmp(command, "exit") == 0)
        {
            break;
        }

        args = parse_args(command);
        if (args[0] != NULL)
        {
            execute_command(args);
        }
        free(args); 
    }

    return EXIT_SUCCESS;
}

void display_prompt(void)
{
    printf("$ ");
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int read_command(char *command, size_t size)
{
    if (fgets(command, size, stdin) == NULL)
    {
        if (feof(stdin))
        {
            printf("\n");
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }
    }

    command[strcspn(command, "\n")] = '\0';

    return 1;
}

char **parse_args(char *command)
{
    int argc = 0;
    char **argv = malloc(sizeof(char *) * (COMMAND_SIZE + 1));
    char *token;

    if (argv == NULL)
    {
        perror("Failed to allocate argv");
        exit(EXIT_FAILURE);
    }

    token = strtok(command, " \t");
    while (token != NULL && argc < COMMAND_SIZE)
    {
        argv[argc++] = token;
        token = strtok(NULL, " \t");
    }
    argv[argc] = NULL;

    return argv;
}

void execute_command(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("failed to execute");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
    }
}

void sigint_handler(int unused)
{
    (void)unused;
    printf("\n");
    fflush(stdout); 
}

