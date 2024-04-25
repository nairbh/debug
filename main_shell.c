#include "shell.h"
/**
 * main - The main function for a simple shell program
 *
 * Description: this program create a basic shell
 * accepting and executing command entered by the user
 * 
 * Return: Always 0
 */

int main(int argc, char **argv, char **env) {
    char *input = NULL;
    char **args = NULL;
    char *command = NULL;
    size_t input_size = 0;
    ssize_t n_char = 0;
    char *line;
     (void)argc;
   while (1) {
        if (isatty(STDIN_FILENO)) {
            printf("Cisfun$ ");
        }
        n_char = getline(&input, &input_size, stdin);
        if (n_char == -1) {
            free(input);
            break;
        }
        if (input[n_char - 1] == '\n') {
            input[n_char - 1] = '\0';
        }
        line = strtok(input, "\n");
        while (line != NULL) {
            if (!check_spaces_tabs(line)) {
                args = split_string(line, &command);
                if (args == NULL) {
                    line = strtok(NULL, "\n");
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
            line = strtok(NULL, "\n");
        }
        free(input);
        input = NULL;
        input_size = 0;
    }
    return 0;
}
