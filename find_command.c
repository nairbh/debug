#include "shell.h"
/**
 * find_command - Function that find the path of command
 * @args: array of string command to find
 *
 * Return: the pointer to path search
 */
char *find_command(char *args)
{
int i = 0;
char path_search[4096];
const char *path[] = {"/bin", "/usr/bin", NULL};
if (access(args, X_OK) == 0)
{
return (strdup(args));
}
while (path[i] != NULL)
{
sprintf(path_search, "%s/%s", path[i], args);
if (access(path_search, X_OK) == 0)
{
return (strdup(path_search));
}
i++;
}
return (NULL);
}
