#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define COMMAND_SIZE 128

extern char **environ;
char **parse_args(char *command);
void execute_command(char **args);
int read_command(char *command, size_t size);
void display_prompt(void);
void sigint_handler(int unused);
char *find_executable(const char *command);

int main(void) {
    char command[COMMAND_SIZE];
    char **args;
    int is_interactive = isatty(STDIN_FILENO);

    signal(SIGINT, sigint_handler);

    while (1) {
        if (is_interactive) {
            display_prompt();
        }

        if (!read_command(command, sizeof(command))) {
            continue;
        }

        if (strcmp(command, "exit") == 0) {
            break;
        }
        if (strcmp(command, "env") == 0)
        {
            char **env;
            for(env = environ; *env != NULL; env++)
            {
                printf("%s", *env);
            }
        }

        args = parse_args(command);
        if (args && args[0]) {
            execute_command(args);
        }
        free(args);
    }

    return EXIT_SUCCESS;
}

void display_prompt(void) {
    printf("$ ");
}

int read_command(char *command, size_t size) {
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

char **parse_args(char *command) {
     char *token = NULL;
    int argc = 0;
    char **argv = malloc(sizeof(char *) * (COMMAND_SIZE + 1));
    if (argv == NULL) {
        perror("Failed to allocate argv");
        exit(EXIT_FAILURE);
    }
    token = strtok(command, " \n\t");
    while (token != NULL && argc < COMMAND_SIZE) {
        argv[argc++] = token;
        token = strtok(NULL, " \n\t");
    }
    argv[argc] = NULL;

    return argv;
}

void execute_command(char **args) {

    pid_t pid;
    char *executable_path = find_executable(args[0]);
    if (!executable_path) {
        fprintf(stderr, "Command not found: %s\n", args[0]);
        return;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execve(executable_path, args, environ) == -1) {
            perror("execution failed");
            exit(EXIT_FAILURE);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
    }

    free(executable_path);
}

char *find_executable(const char *command) {
    const char *path;
     char *result = NULL;
    char *path_copy;
    char *token = NULL;
    if (strchr(command, '/')) {
        if (access(command, X_OK) == 0) {
            return strdup(command);
        }
        return NULL;
    }

   path = getenv("PATH");
    if (!path) return NULL;

    
    path_copy = strdup(path);
   
    token = strtok(path_copy, ":");

    while (token != NULL) {
        char *full_path = malloc(strlen(token) + strlen(command) + 2);
        sprintf(full_path, "%s/%s", token, command);

        if (access(full_path, X_OK) == 0) {
            result = strdup(full_path);
            free(full_path);
            break;
        }

        free(full_path);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return result;
}

void sigint_handler(int unused) {
    (void)unused;
    printf("\n");
    fflush(stdout);
}
