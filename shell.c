#include "shell.h"

/**
 * main - Entry point of the program
 *
 * Description: This function serves as the entry point of the program.
 * It contains the main loop that repeatedly prompts the user for input,
 * reads the input command, and executes it until the user enters the
 * "exit" command.
 * Signals are also handled within this function.
 *
 * Return: Always returns EXIT_SUCCESS upon successful completion.
 */
 int main(void) {
    char command[128];
    int is_interactive = isatty(STDIN_FILENO);
    signal(SIGINT, SIG_IGN); // Ignore SIGINT in parent

    if (is_interactive) {
        display_prompt();
    }

    while (1) {
        if (fgets(command, sizeof(command), stdin) == NULL) {
            if (feof(stdin)) { // Handle EOF
                printf("\n");
                exit(EXIT_SUCCESS);
            } else {
                perror("Error reading input");
                continue;
            }
        }
        command[strcspn(command, "\n")] = '\0'; // Remove newline character

        if (strcmp(command, "exit") == 0) {
            break;
        }

        execute_command(command);

        if (is_interactive) {
            display_prompt();
        }
    }

    return EXIT_SUCCESS;
}