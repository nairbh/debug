#include "shell.h"

/**
 * _execute_command - executes a command provided by the user
 *
 * @argv: main program arguments
 * @command: array of string as command and its arguments
 * @env: environment
 *
 * Return: 0 on success, otherwise 1
 */
void execute_command(char **argv, char **command, char **env)
{
	pid_t child;
	int status;
	char *cmd = find_command(command[0]);

	if (cmd == NULL)
	{
	  printf("non reussi");
		free(cmd);
		if (isatty(STDIN_FILENO))
		  
		exit(EXIT_FAILURE);
	}

	if (argv == NULL)
	{
		free_token_command(command);
		free(cmd);
		
	}

	child = fork();

	if (child < 0)
	{
		perror("fork");
		free_token_command(command);
		free(cmd);
		exit(1);
	}
	else if (child == 0)
		execve(cmd, command, env);
	else
	{
		free(cmd);
		waitpid(child, &status, 0);
	}
	
}
