#include "shell.h"
/**
 * free_token_command - Function that free the memory
 * allocated dynamicly
 * @token: the array of token to free
 *
 */
void free_token_command(char **token)
{
int i;
if (token == NULL || *token == NULL)
return;
for (i = 0; token[i] != NULL; i++)
{
free(token[i]);
}
free(token);
}
