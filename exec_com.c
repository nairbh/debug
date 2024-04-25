#include "shell.h"


/**
 * custom_execlp - Executes a file with given arguments
 * @file: The file to be executed
 * @arg0: The first argument to pass to the file
 *        (usually the name of the file)
 * @...: The rest of the arguments to pass to the file
 *
 * Description: This function is a custom version of execlp.
 *              It takes a file and a variable number of arguments,
 *              and executes the file with those arguments.
 *              The function uses execvp to execute the file,
 *              and perror to print an error message if the file
 *              is not found.
 *
 * Return: If the function succeeds, it does not return.
 *         If the function fails (and errno is set to ENOENT),
 *         it returns -1.
 */
int custom_execlp(const char *file, const char *arg0, ...)
{
	int i = 1;
	va_list args;
	const char *argv[10];

	argv[0] = arg0;
	va_start(args, arg0);

	while ((argv[i] = va_arg(args, const char *)) != NULL && i < 9)
	{
		i++;
	}
	va_end(args);
	argv[i] = NULL;

	if (execvp(file, (char *const *)argv) == -1 && errno == ENOENT)
	{
		perror(argv[0]);
		return (-1);
	}
	return (0);
}

/**
 * execute_command - Executes a command passed as a string
 * @command: The command to be executed
 *
 * Description: This function forks the current process and executes the
 * command
 * passed as a string. It first tokens the command string into arguments using
 * spaces and tabs as delimiters. If the command is "exit", it exits the child
 * process. If the command is empty, it displays the prompt and exits the child
 * process. If the command is not "exit" and not empty, it uses execvp to
 * replace the child process with the command. If execvp fails, it prints an
 * error message and exits the child process. The parent process waits for the
 * child process to finish executing the command.
 *
 * Return: This function does not return a value
 */
void execute_command(const char *command)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	else if (child_pid == 0)
	{
		char *args[10];
		char *token = strtok((char *)command, DELIMITER);
		int i = 0;

		while (token != NULL && i < 10)
		{
			args[i++] = token;
			token = strtok(NULL, DELIMITER);
		}
		args[i] = NULL;
		if (i == 0)
		{
			display_prompt();
			exit(EXIT_SUCCESS);
		}
		if (strcmp(args[0], "exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}
		if (execvp(args[0], args) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}
