#include "main.h"
/**
 * flush_buffer - Writes the buffer contents using _putchar
 * @buffer: The buffer to flush
 * @buffer_index: Pointer to the buffer index
 * Return: Number of characters written
 */
int flush_buffer(char *buffer, int *buffer_index)
{
	int count;

	count = write(1, buffer, *buffer_index);
	*buffer_index = 0;
	return (count);
}

/**
 * _printf - Produces output according to a format
 * @format: Character string containing zero or more directives
 * Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0, buffer_index = 0;
	char buffer[BUFFER_SIZE];
	format_t formats[] = {
		{'c', print_char},
		{'s', print_string},
		{'d', print_int},
		{'i', print_int},
		{'R', print_rot13string},
		{'o', print_octal},
		{'u', print_unsigned_int},
		{'x', print_lower_hex},
		{'X', print_upper_hex},
		{'r', print_reverse},
		{'b', print_binary},
		{0, NULL}
	};

	if (!format)
		return (-1);

	va_start(args, format);
	count = process_format(format, args, buffer, &buffer_index, formats);
	va_end(args);

	if (buffer_index > 0)
		flush_buffer(buffer, &buffer_index);

	return (count);
}

/**
 * process_format - Process the format string for _printf
 * @format: The format string to process
 * @args: List of variadic arguments
 * @buffer: Buffer to store output characters
 * @buffer_index: Pointer to the current index in the buffer
 * @formats: Array of format specifiers and their corresponding functions
 *
 * Return: Number of characters processed and added to the buffer
 */
int process_format(const char *format, va_list args, char *buffer,
int *buffer_index, format_t *formats)
{
	int i = 0, count = 0;

	while (format[i])
	{
		if (format[i] != '%')
		{
			buffer[(*buffer_index)++] = format[i];
			count++;
			if (*buffer_index == BUFFER_SIZE)
				count += flush_buffer(buffer, buffer_index);
		}
		else
		{
			i++;
			if (format[i] == '\0')
				return (-1);
			count += handle_format(format[i], formats, args, buffer, buffer_index);
		}
		i++;
	}
	return (count);
}

/**
 * handle_format - Handles formatting for _printf
 * @spec: Format specifier
 * @formats: Array of format structs
 * @args: List of arguments
 * @buffer: Buffer for output
 * @buffer_index: Current index in buffer
 * Return: Number of characters handled
 */
int handle_format(char spec, format_t *formats, va_list args,
				char *buffer, int *buffer_index)
{
	int j;

	if (spec == '%')
	{
		buffer[(*buffer_index)++] = '%';
		if (*buffer_index == BUFFER_SIZE)
			return (1 + flush_buffer(buffer, buffer_index));
		return (1);
	}

	for (j = 0; formats[j].spec != 0; j++)
		if (spec == formats[j].spec)
			return (formats[j].f(args, buffer, buffer_index));

	buffer[(*buffer_index)++] = '%';
	buffer[(*buffer_index)++] = spec;
	return (2);
}
