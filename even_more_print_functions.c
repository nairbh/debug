#include "main.h"

/**
 * print_binary - Prints an unsigned integer in binary format
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @buffer_index: Index at which to add next char, represents the length
 *
 * Return: Number of chars printed
 */
int print_binary(va_list args, char *buffer, int *buffer_index)
{
	unsigned int n = va_arg(args, unsigned int);
	unsigned int mask = 1U << 31;
	int started = 0;
	int count = 0;

	if (n == 0)
	{
		buffer[(*buffer_index)++] = '0';
		return (1);
	}

	while (mask > 0)
	{
		if (n & mask)
		{
			buffer[(*buffer_index)++] = '1';
			started = 1;
			count++;
		}
		else if (started)
		{
			buffer[(*buffer_index)++] = '0';
			count++;
		}

		if (*buffer_index == BUFFER_SIZE)
			count += flush_buffer(buffer, buffer_index);

		mask >>= 1;
	}

	return (count);
}
