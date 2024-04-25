#include "shell.h"

/**
 * user_input - Reads user input from stdin and stores it in the provided
 * buffer.
 * @command: Pointer to the buffer where the user input will be stored.
 * @size: Maximum size of the buffer.
 *
 * This function reads a line of input from the standard input (stdin) and
 * stores
 * it in the buffer pointed to by @command. The input is terminated by a
 * newline
 * character ('\n') or when the buffer is full. If the input is successfully
 * read and stored, the newline character at the end of the input is replaced
 * with a null terminator ('\0') to properly terminate the string.
 *
 * If an error occurs during reading or if the end-of-file (EOF) is reached
 * without any input, the function prints an error message using perror() and
 * exits the program with EXIT_FAILURE status. If the end-of-file is reached
 * without any input (e.g., the user presses Ctrl+D), the program exits with
 * EXIT_SUCCESS status.
 */
void user_input(char *command, size_t size)
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
			perror("fgets");
			exit(EXIT_FAILURE);
		}
	}

	command[strcspn(command, "\n")] = '\0';
}

/**
 * read_command - Reads a command from standard input
 * @command: Pointer to a character array to store the command
 * @size: Size of the command array
 *
 * Description: This function reads a command from standard input and stores it
 *              in the provided character array. If the end of file is reached,
 *              it prints a newline and exits successfully. If there's an error
 *              while reading the input, it prints an error message and exits
 *              with failure. The function also removes any trailing newline
 *              character from the input.
 */
void read_command(char *command, size_t size)
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
			printf("Error while reading input.\n");
			exit(EXIT_FAILURE);
		}
	}
	command[strcspn(command, "\n")] = '\0';
}

/**
 * sigint_handler - Handles the SIGINT signal
 * @signum: The signal number (unused in this function)
 *
 * Description: This function is called when the SIGINT signal is received.
 *		It prints a newline character and resets the signal handler to
 *		its default behavior.
 */
void sigint_handler(int signum)
{
	static int sigint_received;
	(void) signum;

	if (!sigint_received)
	{
		sigint_received = 1;
		signal(SIGINT, SIG_IGN);
		printf("\n");
		display_prompt();
		fflush(stdout);
		signal(SIGINT, sigint_handler);
		sigint_received = 0;
	}
}
