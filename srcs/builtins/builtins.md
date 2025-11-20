# BUILTINS
## [echo](https://www.ibm.com/docs/es/aix/7.2.0?topic=e-echo-command)
	- output the args separated bu spaces, terminated with a newline (if -n is not indicated)
 	- if set, the echo builtin expands backslash-escape sequences by default.

###	RETURN VALUE:
		0 if success
		1 else

## [exit](https://www.geeksforgeeks.org/linux-unix/exit-command-in-linux-with-examples/)
	- Imprimir "exit": Siempre debe escribir "exit" en stderr (o stdout) si es interactivo.
	- Sin argumentos: Sale con el último código de error global (g_status o $?).
	- Argumento no numérico: Imprime error (numeric argument required) y sale con código 2.
	- Demasiados argumentos:
	- Si el primero es un número: Imprime error (too many arguments) y NO sale (retorna 1).
	- Overflow: Debe manejar números mayores que long long (tratándolos como no numéricos).

###	RETURN VALUE:
		0 EXIT_SUCCESS indicates no error
		1 EXIT_FAILURE encountered minor errors
		2 indicate the misuse of shell bultins
## [cd](https://www.ibm.com/docs/es/aix/7.3.0?topic=c-cd-command)
	- uses the function [chdir](https://man7.org/linux/man-pages/man2/chdir.2.html)
	- the `cd` command sets the current working directory of a process. The user must have execute (search) permission in the specified directory
 	- if used without parameters, cd displays the current drive and directory.
		- if command extensions are enabled:
	 	- the current directory string is converted to use the same case as the names on the disk. For example, cd c:\temp would set the current directory to C:\Temp if that is the case on the disk.
		- spaces aren't treated as delimiters, so <path> can contain spaces without enclosing quotation marks
		- [curpath](https://unix.stackexchange.com/questions/621596/what-does-curpath-stand-for) is like a "temporary variable". Let's say that initially it is defined and assigned a dummy value. The following steps can modify its value, and finally curpath will hold the result of the processing.
### ALGORITM
	1.	get the current directory ($OLDPWD)
	2.	get the destination directory
		- if theres no destination, change to $HOME
		- if the argument is -, no action ($HOME = $OLDPWD)
		- assign the value of the argument to the current directory
	3.	change directory
		- if chdir fails it returns -1
		- if it doesnt, actualizate old and current path with getcwd
			- uses the [setenv](https://man7.org/linux/man-pages/man3/setenv.3.html) function which is not allowed in the subject
	int set_env(const char *name, const char *value, int ow)
### BEHAVIOR
	If, during the execution of the above steps, the PWD environment
	variable is set, the OLDPWD environment variable shall also be set
	to the value of the old working directory (that is the current
	working directory immediately prior to the call to cd).
###	RETURN VALUE:
	- 0 if success
	- 1 if failure. In case it does, chdir() returns an [errno](https://man7.org/linux/man-pages/man3/errno.3.html) defined value

## [pwd](https://www.geeksforgeeks.org/linux-unix/pwd-command-in-linux-with-examples/)
	- uses the function [getcwd()](https://pubs.opengroup.org/onlinepubs/007904975/functions/getcwd.html)
	- print the name of current/working directory on the standard output
	- the getcwd() function shall fail if:
		[EINVAL] The size argument is 0.
		[ERANGE] The size argument is greater than 0, but is smaller than the length of the pathname +1.
		[EACCES] Read or search permission was denied for a component of the pathname.
		[ENOMEM] Insufficient storage space is available.-> uses the [getcwd](https://pubs.opengroup.org/onlinepubs/007904975/functions/getcwd.html) function
###	RETURN VALUE:
		0	in case getcwd doesn't fail
		>0	in case it does
		getcwd returns a NULL pointer in case of error or the buf argument in case of success.

## [unset](https://man7.org/linux/man-pages/man1/unset.1p.html)
	Each variable or function specified by name shall be unset.
	VARIABLE = is not equivalent to an unset of VARIABLE; in the example, VARIABLE is set to "".
###	RETURN VALUE:
		0    All name operands were successfully unset.
       >0    At least one name could not be unset.
## [export](https://www.geeksforgeeks.org/linux-unix/export-command-in-linux-with-examples/)
	- It allows variables to be available in the current shell session and any child processes, which helps in setting up and configuring your shell environment dynamically.
	- The shell shall format the output, including the proper use of quoting, so that it is suitable for reinput to the shell as commands that achieve the same exporting results, except:
		1. Read-only variables with values cannot be reset.
		2. Variables that were unset at the time they were output need not be reset to the unset state if a value is assigned to the variable between the time the state was saved and the time at which the saved output is reinput to the shell.
       When no arguments are given, the results are unspecified.
	if the value given is null or a empty string then the node is not visibile
###	RETURN VALUE:

## [env](https://man7.org/linux/man-pages/man1/env.1.html)
	Set each name to value in the enviroment and run command
### ENVIROMENT VARIABLE
	### [env file](https://www.ibm.com/docs/es/aix/7.2.0?topic=files-env-file)
		The .env file is a system boot file which allows you to customize individual working environment variables
