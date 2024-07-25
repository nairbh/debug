#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

/**
 * struct format - Struct for format specifiers
 * @spec: The format specifier
 * @f: The function associated
 */
typedef struct format
{
	char spec;
	int (*f)(va_list, char*, int*);
} format_t;

/* function definitions */

int _printf(const char *format, ...);
int process_format(const char *format, va_list args, char *buffer,
					int *buffer_index, format_t *formats);
int print_char(va_list args, char *buffer, int *buffer_index);
int print_string(va_list args, char *buffer, int *buffer_index);
int print_int(va_list args, char *buffer, int *buffer_index);
int handle_format(char spec, format_t *formats, va_list args,
		char *buffer, int *buffer_index);
int flush_buffer(char *buffer, int *buffer_index);
int print_number(unsigned int n, char *buffer, int *buffer_index);
int print_rot13string(va_list args, char *buffer, int *buffer_index);
int print_octal(va_list args, char *buffer, int *buffer_index);
int print_unsigned_int(va_list args, char *buffer, int *buffer_index);
int print_lower_hex(va_list args, char *buffer, int *buffer_index);
int print_upper_hex(va_list args, char *buffer, int *buffer_index);
int print_reverse(va_list args, char *buffer, int *buffer_index);
int print_binary(va_list args, char *buffer, int *buffer_index);

#endif /* MAIN_H */
