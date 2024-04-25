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
 */#include "shell.h"
/**
 * execute_command - forks a new process and executes the command
 * @command: the command to be executed and its arguments
 * Return: void
 */
void execute_command(char **command)
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
		if (execve(command[0], command, environ) == -1)
		{
			perror("failed execute");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
/**
 * find_execute_command - finds the path to the executable and executes the command
 * @command: the command to be executed
 * @executable_path: the path to the executable
 * 
 * Return: 1 if the executable was found, 0 otherwise
 */
int find_execute_command(char *command, char *executable_path)
{
	int found_executable = 0;
	int i;
	char **argv = parse_args(command);

	if (argv[0] == NULL)
	{
	free(argv);
	return (0);
	}

	else
	{
	char *path_env = {"/bin", "/usr/bin", NULL};

	if (path_env)
	{
	char *path_env_copy = strdup(path_env);
	char *token = strtok(path_env_copy, ":");
	while (token != NULL)
	{
	strcpy(executable_path, token);
	strcat(executable_path, "/");
	strcat(executable_path, argv[0]);


	token = strtok(NULL, ":");
	}
	free(path_env_copy);
	free(path_env);
	}
	}

        for (i = 1; argv[i] != NULL; i++)
	{
	argv[0] = executable_path;
	strcat(executable_path, " ");
	strcat(executable_path, argv[i]);
	}

	free(argv);
	return (found_executable);
}

char **parse_args(char *command)
{

	char *token;
	int argc = 0;
	char **argv = malloc(sizeof(char *) * (buffer + 1));


	if (argv == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(command, " \t");

	while (token != NULL)
	{

	if (argc >= COMMAND_SIZE)
	{
	fprintf(stderr, "Too many arguments\n");
	free(argv);
	exit(EXIT_FAILURE);
	}
	argv[argc++] = token;
	token = strtok(NULL, " \t");
	}
	
	argv[argc] = NULL;

	return (argv);
}