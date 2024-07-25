# _printf

_printf is a project for Holberton School which imitates the "printf()" function found in the "stdio.h" library.

_printf allows users to print a variety of characters and variables on their terminal.

## Project Tests

This project was tested using these compilation flags :
`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format *.c`

This project was subjected to multiple tests using the main.c file which we included here:
```c
#include <limits.h>
#include <stdio.h>
#include "main.h"

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
    int len;
    int len2;
    unsigned int ui;
    void *addr;

    len = _printf("Let's try to printf a simple sentence.\n");
    len2 = printf("Let's try to printf a simple sentence.\n");
    ui = (unsigned int)INT_MAX + 1024;
    addr = (void *)0x7ffe637541f0;
    _printf("Length:[%d, %i]\n", len, len);
    printf("Length:[%d, %i]\n", len2, len2);
    _printf("Negative:[%d]\n", -762534);
    printf("Negative:[%d]\n", -762534);
    _printf("Unsigned:[%u]\n", ui);
    printf("Unsigned:[%u]\n", ui);
    _printf("Unsigned octal:[%o]\n", ui);
    printf("Unsigned octal:[%o]\n", ui);
    _printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui);
    printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui);
    _printf("Character:[%c]\n", 'H');
    printf("Character:[%c]\n", 'H');
    _printf("String:[%s]\n", "I am a string !");
    printf("String:[%s]\n", "I am a string !");
    _printf("Address:[%p]\n", addr);
    printf("Address:[%p]\n", addr);
    len = _printf("Percent:[%%]\n");
    len2 = printf("Percent:[%%]\n");
    _printf("Len:[%d]\n", len);
    printf("Len:[%d]\n", len2);
    _printf("Unknown:[%r]\n");
    printf("Unknown:[%r]\n");
    _printf("Rot13 : [%R]\n", "Awesome!");
    printf("Rot13 : [%R]\n", "Awesome!");
    return (0);
}
```

Output:
```c
Let's try to printf a simple sentence.
Let's try to printf a simple sentence.
Length:[39, 39]
Length:[39, 39]
Negative:[-762534]
Negative:[-762534]
Unsigned:[2147484671]
Unsigned:[2147484671]
Unsigned octal:[20000001777]
Unsigned octal:[20000001777]
Unsigned hexadecimal:[800003ff, 800003FF]
Unsigned hexadecimal:[800003ff, 800003FF]
Character:[H]
Character:[H]
String:[I am a string !]
String:[I am a string !]
Address:[%p]
Address:[0x7ffe637541f0]
Percent:[%]
Percent:[%]
Len:[12]
Len:[12]
Unknown:[%r]
Unknown:[%r]
Rot13 : [Njfbzr!]
Rot13 : [%R]

```
## Man-page Installation

To install the man-page use the following commands :
```c
sudo mkdir /usr/local/man/man3
sudo install -g 0 -o 0 -m 0644 man_3_printf /usr/local/man/man3/_printf.3
sudo gzip /usr/local/man/man3/_printf.3
sudo mandb
```
## Files

|File |Description |
|---------------------|------------------------------------------------------------------------------|
|main.h | Header file containing function prototypes and necessary includes |
|_printf.c | Main file containing functions to print regular characters and detect specifiers used |
|print_functions.c | File containing the different functions that allow _printf.c to print variables |
|more_print_functions.c | File containing additional functions that allow _printf.c to print variables |
|man_3_printf | Text file containing information about _printf |
|Flowchart_printf.jpg | Image file containing a flowchart that showcases how _printf functions |


## Usage

For the function "_printf()" to work , the correct specifiers needs to be used.
The list of all current working specifiers is provided and updated here :

|Variable Type  |Specifier |
|---------------|----------|
|String |%s |
|Integer |%d |
|Character |%c |
|Integer base 10|%i |
|Percent symbol |%% |
|Rot13 |%R |
|unsigned int |%u |
|Integer base 8 |%o |
|integer base 16|%x & %X|

When the function "_printf()" is succesful in printing the data sent to it, the return value is a count of all characters printed, else if it fails to print, the return value is -1.

## Examples

Basic single character example:
```c
char character = 'C';

_printf("I %c you", character);
```
Result :
`I C you`


Basic string example:
```c
char str_to_print[] = "world!";

_printf("Hello %s", str_to_print);
```
Result :
`Hello world!`


Basic integer example:
```c
int number = 404;

_printf("If you see %d, you are lost", number);
```
Result :
`If you see 404, you are lost`


Advanced example:
```c
int number = 0;
char str_to_print[] = "is a well rounded number";

_printf("The number %d %s", number, str_to_print);
```
Result :
`The number 0 is a well rounded number`


## Contributors

This project was made by , Fassih Belmokhtar and José Puertas

## Special Mention

# Holberton School

This project was made possible by Holberton School
