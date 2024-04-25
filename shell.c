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
extern char **environ;

int main(void)
{
    char command[COMMAND_SIZE];
    char **args;
    int is_interactive = isatty(STDIN_FILENO);

    signal(SIGINT, sigint_handler);

    while (1)
    {
        if (is_interactive) {
            display_prompt();
        }

        if (!read_command(command, sizeof(command))) {
            continue;  
        }

        if (strcmp(command, "exit") == 0) {
            break; 
        }

        if (strcmp(command, "env") == 0) {
            char **env;
            for(env = environ; *env != NULL; env++) {
                printf("%s\n", *env);
            }
            continue; 
        }

        args = parse_args(command);
        if (args && args[0]) {
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

int read_command(char *command, size_t size)
{
    if (fgets(command, size, stdin) == NULL) {
        if (feof(stdin)) { 
            printf("\n");
            exit(EXIT_SUCCESS);
        } else {
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
    char *token = NULL;
    char **argv = malloc(sizeof(char *) * (COMMAND_SIZE + 1));
    if (argv == NULL) {
        perror("Failed to allocate argv");
        exit(EXIT_FAILURE);
    }

    token = strtok(command, " \t");
    while (token != NULL && argc < COMMAND_SIZE) {
        argv[argc++] = token;
        token = strtok(NULL, " \t");
    }
    argv[argc] = NULL;

    return argv;
}

void execute_command(char **args)
{
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("execution failed");
            exit(EXIT_FAILURE);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

void sigint_handler(int unused)
{
    (void)unused;
    printf("\n");
    fflush(stdout); 
}
