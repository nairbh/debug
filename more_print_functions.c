#include "main.h"

/**
 * print_octal - Prints an octal
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @buffer_index: Index at which to add next char, represents the length
 *
 * Return: Number of chars printed
 */
int print_octal(va_list args, char *buffer, int *buffer_index)
{
	unsigned int n = va_arg(args, int);
	int count = 0, i = 0, num = 0;
	char octal[BUFFER_SIZE];

	if (n == 0)
	{
		octal[i] = num + '0';
		i++;
	}
	while (n > 0)
	{
		num = n % 8;
		n = n / 8;
		octal[i] = num + '0';
		i++;
	}
	while (i > 0)
	{
		i--;
		buffer[(*buffer_index)++] = octal[i];
		count++;
		if (*buffer_index == BUFFER_SIZE)
		{
			flush_buffer(buffer, buffer_index);
		}
	}
	return (count);
}

/**
 * print_unsigned_int - Prints an unsigned int
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @buffer_index: Index at which to add next char, represents the length
 *
 * Return: Number of digits printed
 */
int print_unsigned_int(va_list args, char *buffer, int *buffer_index)
{
	unsigned int n = va_arg(args, int);
	int count = 0, num = 0, i = 0;
	char num_tab[BUFFER_SIZE];

	if (n == 0)
	{
		num_tab[i] = num + '0';
		i++;
	}
	while (n > 0)
	{
		num = n % 10;
		n = n / 10;
		num_tab[i] = num + '0';
		i++;
	}
	while (i > 0)
	{
		i--;
		buffer[(*buffer_index)++] = num_tab[i];
		count++;
		if (*buffer_index == BUFFER_SIZE)
		{
			flush_buffer(buffer, buffer_index);
		}
	}
	return (count);
}

/**
 * print_lower_hex - Prints in hex
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @buffer_index: Index at which to add next char, represents the length
 *
 * Return: Number of digits printed
 */
int print_lower_hex(va_list args, char *buffer, int *buffer_index)
{
	unsigned int n = va_arg(args, int);
	int count = 0, num = 0, i = 0, j = 0, in[6] = {10, 11, 12, 13, 14, 15};
	char num_tab[BUFFER_SIZE], out[6] = {'a', 'b', 'c', 'd', 'e', 'f'};

	if (n == 0)
	{
		num_tab[i] = num + '0';
		i++;
	}
	while (n > 0)
	{
		num = n % 16;
		n = n / 16;
		while (j <= 5)
		{
			if (num == in[j])
			{
				num_tab[i] = out[j];
				break;
			}
			j++;
		}
		if (num <= 9 && num >= 0)
		{
		num_tab[i] = num + '0';
		}
		j = 0;
		i++;
	}
	while (i > 0)
	{
		i--;
		buffer[(*buffer_index)++] = num_tab[i];
		count++;
		if (*buffer_index == BUFFER_SIZE)
		{
			flush_buffer(buffer, buffer_index);
		}
	}
	return (count);
}

/**
 * print_upper_hex - Prints in hex
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @buffer_index: Index at which to add next char, represents the length
 *
 * Return: Number of digits printed
 */
int print_upper_hex(va_list args, char *buffer, int *buffer_index)
{
	unsigned int n = va_arg(args, int);
	int count = 0, num = 0, i = 0, j = 0, in[6] = {10, 11, 12, 13, 14, 15};
	char num_tab[BUFFER_SIZE], out[6] = {'A', 'B', 'C', 'D', 'E', 'F'};

	if (n == 0)
	{
		num_tab[i] = num + '0';
		i++;
	}
	while (n > 0)
	{
		num = n % 16;
		n = n / 16;
		while (j <= 5)
		{
			if (num == in[j])
			{
				num_tab[i] = out[j];
				break;
			}
			j++;
		}
		if (num <= 9 && num >= 0)
		{
		num_tab[i] = num + '0';
		}
		j = 0;
		i++;
	}
	while (i > 0)
	{
		i--;
		buffer[(*buffer_index)++] = num_tab[i];
		count++;
		if (*buffer_index == BUFFER_SIZE)
			flush_buffer(buffer, buffer_index);
	}
	return (count);
}

/**
 * print_reverse - Prints a string in reverse
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @buffer_index: Index at which to add next char, represents the length
 *
 * Return: Number of chars printed
 */
int print_reverse(va_list args, char *buffer, int *buffer_index)
{
	char *str;
	int i, count = 0;

	str = va_arg(args, char *);

	if (str == NULL)
	{
		str = ")Null(";
	}

	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		buffer[(*buffer_index)++] = str[i];
		count++;
		if (*buffer_index == BUFFER_SIZE)
		{
			count += flush_buffer(buffer, buffer_index);
		}
	}

	return (count);
}
