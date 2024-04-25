#include "shell.h"
/**
 * split_string - split an input string into an array of arguments
 * @input: The user input string to split
 * @command: the command to split
 * Return: An array of splited arguments,
 * or NULL on failure.
 */
char **split_string(char *input, char **command)
{
   char **args = NULL;
    char *delim = " \n\t";
    char *token;
    size_t i = 0, buffer = 2;
    token = strtok(input, delim);
    if (token != NULL)
      {
        *command = strdup(token);
        if (*command == NULL) {
            perror("allocation non reussi");
            exit(EXIT_FAILURE);
        }
    }
    args = malloc(buffer * sizeof(char *));
        if (!args) {
        perror("allocation echouer");
        exit(EXIT_FAILURE);
    }
      while (token != NULL)
    {
        if (i >= buffer - 1) {
            buffer *= 2;
            args = my_realloc(args, i * sizeof(char *), buffer * sizeof(char *));
            if (!args) {
                perror("echouer");
                exit(EXIT_FAILURE);
            }
        }
        args[i++] = strdup(token);
        if (args[i - 1] == NULL)
        {
            perror("allocation non reussi");
            exit(EXIT_FAILURE);
        }
        token = strtok(NULL, delim);
    }
    args[i] = NULL;
    return (args);
}
