#include "main.h"

/**
 * print_int - Prints an integer
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @buffer_index: Index at which to add next char, represents the length
 *
 * Return: Number of chars printed
 */
int print_int(va_list args, char *buffer, int *buffer_index)
{
	int n = va_arg(args, int);
	int count = 0;
	unsigned int num = (n < 0) ? -n : n;

	if (n < 0)
		buffer[(*buffer_index)++] = '-', count++;

	count += print_number(num, buffer, buffer_index);
	return (count);
}

/**
 * print_number - Recursively prints an unsigned integer
 * @n: Number to print
 * @buffer: Buffer array to handle print
 * @buffer_index: Index at which to add next char, represents the length
 *
 * Return: Number of digits printed
 */
int print_number(unsigned int n, char *buffer, int *buffer_index)
{
	int count = 0;

	if (n / 10)
		count += print_number(n / 10, buffer, buffer_index);

	buffer[(*buffer_index)++] = (n % 10) + '0';
	count++;
	if (*buffer_index == BUFFER_SIZE)
		flush_buffer(buffer, buffer_index);

	return (count);
}

/**
 * print_char - function to print chars
 * @arg: va_list type
 * @buffer: Buffer array to handle print
 * @buffer_index: Index at which to add next char, represents the length
 *
 * Return: Number of characters printed
 */
int print_char(va_list arg, char *buffer, int *buffer_index)
{
	int c;

	c = va_arg(arg, int);
	buffer[(*buffer_index)++] = c;
	if (*buffer_index == BUFFER_SIZE)
	{
		flush_buffer(buffer, buffer_index);
	}
	return (1);
}

/**
 * print_string - function to print strings
 * @arg: va_list type
 * @buffer: Buffer array to handle print
 * @buffer_index: Index at which to add next char, represents the length
 *
 * Return: Number of characters printed
 */
int print_string(va_list arg,  char *buffer, int *buffer_index)
{
	int count = 0;
	char *str = va_arg(arg, char*);

	if (str == NULL)
		str = "(null)";

	while (str[count])
	{
		buffer[(*buffer_index)++] = str[count];
		if (*buffer_index == BUFFER_SIZE)
			flush_buffer(buffer, buffer_index);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - Print a string in ROT13
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @buffer_index: Index at which to add next char, represents the length
 *
 * Return: Number of chars printed
 */
int print_rot13string(va_list args, char *buffer, int *buffer_index)
{
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(args, char *);
	if (str == NULL)
		str = "(AHYY)";

	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				buffer[*buffer_index] = out[j];
				(*buffer_index)++;
				count++;
				if (*buffer_index == BUFFER_SIZE)
					count += flush_buffer(buffer, buffer_index);
				break;
			}
		}
		if (!in[j])
		{
			buffer[*buffer_index] = str[i];
			(*buffer_index)++;
			count++;
			if (*buffer_index == BUFFER_SIZE)
				count += flush_buffer(buffer, buffer_index);
		}
	}

	return (count);
}
