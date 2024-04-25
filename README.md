# holbertonschool-simple_shell


## What is Shell

Shell is a command-line interpreter providing a user interface to access the operating system's services. This project involves the development of a sh-type shell program (Bourne Shell), typically used through a terminal emulator.
What is it for

The shell interprets commands. It incorporates features such as process control, input/output redirection, and is used to write batch programs or scripts. Unix-like systems all have at least one Bourne shell-compatible interpreter.
Project Information
Environment

OS: Ubuntu 20.04 LTS
Language: C
Compiler: gcc 9.3.0
Editor: VIM 8.1.2269
Version control: Git
Style: Betty style
General Requirements

Use of vi, vim, emacs editors
Compilation on Ubuntu 14.04 LTS with gcc 4.8.4
Compliance with Betty style, without memory leaks
Output identical to sh (/bin/sh)
Authorized Functions

List of authorized functions such as execve, exit, fork, malloc, write, etc.
Compilation Link

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
Documentation

## Installation
Instructions for cloning the repository, changing directories, compiling, and running the shell in interactive or non-interactive mode.
Tests
Example of execution and output after compilation.

$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$

$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2

## Files

Description and links to different project files, such as the manual, scripts, and source code files.

## Flowchart of the function _printf
![Flowchart of the function Simple Shell](flowchart/Flowchart_interactif.jpg?raw=true)

Shell Start: Initializing the environment.
Displaying the Command Prompt: In interactive mode, the shell displays a prompt.
Reading the Command: The shell reads the command line entered by the user.
Analyzing the Command: Identification of the command and arguments.
Executing the Command: Either a built-in command or an external command.
Managing Results: The shell handles results or errors.
Return to Command Prompt or Shell Termination: In interactive mode, return to the command prompt, otherwise termination of the shell.

## Authors
**Jérôme Romand, Néia Santos Nascimento, Sofiane Arfane.**
<br>

**Made for the HOLBERTON SCHOOL - cohort THO-0224**
