#include "shell.h"

/**
* display_prompt - Display the shell prompt
*/
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("#cisfun$ ");
		fflush(stdout);
	}
}

/**
* interactive_mode - Run the shell in interactive mode
*/
void interactive_mode(void)
{
	char *input = NULL;

	size_t input_size = 0;
	ssize_t bytes_read;

	while (1)
	{
		size_t i;

		display_prompt();
		bytes_read = getline(&input, &input_size, stdin);

		if (bytes_read == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				free(input);
				exit(EXIT_SUCCESS);
			}
			else
			{
				perror("Error");
				free(input);
				exit(EXIT_FAILURE);
			}
		}
		for (i = 0; i < (size_t)bytes_read; i++)
		{
			if (input[i] == '\n')
			{
				input[i] = '\0';
				break;
			}
		}

		if (run_command(input) == -1)
		{
			free(input);
			exit(EXIT_FAILURE);
		}
	}
	free(input);
}

/**
* non_interactive_mode - Run the shell in non-interactive mode
*/
void non_interactive_mode(void)
{
	char *input = NULL;

	size_t input_size = 0;
	ssize_t bytes_read;

	while ((bytes_read = getline(&input, &input_size, stdin)) != -1)
	{
		size_t i;

		for (i = 0; i < (size_t)bytes_read; i++)
		{
			if (input[i] == '\n')
			{
				input[i] = '\0';
				break;
			}
		}

		if (run_command(input) == -1)
		{
			free(input);
			exit(EXIT_FAILURE);
		}
	}

	free(input);
}

/**
* run_command - Execute a shell command
* @input: The command to execute
* Return: 0 on success, -1 on failure
*/


int run_command(char *input)
{
    pid_t pid;
    int status;

    char *argv[64];
    char *token;
    int argc = 0;
    char *path_directories[] = {"/bin", "/usr/bin", NULL};
    char exec_path[256];

    // Check if input consists only of spaces or is empty
    char *tmp = input;
    while (*tmp && isspace((unsigned char)*tmp)) {
        tmp++;
    }
    if (*tmp == '\0') {
        return 0; // No command entered, just return 0
    }

    token = strtok(input, " ");
    while (token != NULL && argc < 63)
    {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    argv[argc] = NULL;

    if (argc == 0)
    {
        fprintf(stderr, "No command entered.\n");
        return -1;
    }

    if (argc > 0 && strcmp(argv[0], "exit") == 0)
    {
        free(input);
        exit(EXIT_SUCCESS);
    }

    int found = 0;
    for (int i = 0; path_directories[i] != NULL && !found; i++) {
        snprintf(exec_path, sizeof(exec_path), "%s/%s", path_directories[i], argv[0]);
        if (access(exec_path, X_OK) == 0) {
            found = 1;
        }
    }

    if (!found) {
        fprintf(stderr, "Command not found.\n");
        return -1;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("Error");
        return (-1);
    }
    else if (pid == 0)
    {
        execve(exec_path, argv, NULL);
        perror("Error");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("Error");
            return (-1);
        }
    }
    return (0);
}

/**
* main - Entry point of the shell program
* @argc: Number of command-line arguments
* @argv: Array of command-line arguments
* Return: 0 on success, 1 on failure
*/
int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		if (isatty(STDIN_FILENO))
			interactive_mode();
		else
			non_interactive_mode();
	}
	else
	{
		fprintf(stderr, "Usage: %s [command]\n", argv[0]);
		return (1);
	}
	return (0);
}