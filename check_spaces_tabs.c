#include "shell.h"
/**
 * check_spaces_tabs - Function that check if a string contains
 * only spaces and tabs
 * @input: The string to check
 *
 * Return: 1 if the string contains only spaces and tabs, 0 otherwise.
 */
int check_spaces_tabs(char *input)
{
while (*input != '\0')
{
if (*input != ' ' && *input != '\t')
return (0);
input++;
}
return (1);
}
