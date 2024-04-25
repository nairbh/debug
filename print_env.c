#include "shell.h"
/**
 * print_env - Print environment variables
 */
void print_env(void)
{
	char **env;

	for (env = environ; *env != NULL; env++)
	{
	      
		printf("%s\n", *env);
	}
}
