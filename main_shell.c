#include "shell.h"

int main(int argc, char **argv, char **env) {
    char *input = NULL;
    char **args = NULL;
    char *command = NULL;
    size_t input_size = 0;
    ssize_t n_char = 0;
    int status_return = 1;

    (void)argc;  // Unused parameter

    while (status_return && n_char != EOF) {
        if (isatty(STDIN_FILENO)) {
            printf("Cisfun$ ");
        }
        
        n_char = getline(&input, &input_size, stdin);
        if (n_char == -1) {
            if (feof(stdin)) {  // Check for end of file on stdin
                break;
            }
            perror("Read error");
            continue;
        }

        if (input[n_char - 1] == '\n') {
            input[n_char - 1] = '\0';  // Remove the newline character
        }

        char *line = strtok(input, " \n\t");
        while (line != NULL) {
            if (!check_spaces_tabs(line)) {  // Check if the line is not just spaces or tabs
                args = split_string(line, &command);
                if (args == NULL) {
                    free(line);
                    line = strtok(NULL, "\n\t");
                    continue;
                }
                if (strcmp(args[0], "exit") == 0) {
                    free_token_command(args);
                    free(command);
                    free(input);
                    exit(EXIT_SUCCESS);
                } else if (strcmp(args[0], "env") == 0) {
                    print_env();
                } else {
                    execute_command(argv, args, env);
                }
                free_token_command(args);
                free(command);
            }
            line = strtok(NULL, " \n\t");
        }
        free(input);
        input = NULL;  // Reset input for the next read
        input_size = 0;
    }
    return 0;
}