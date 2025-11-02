# BUILTINS
## [echo](https://www.ibm.com/docs/es/aix/7.2.0?topic=e-echo-command)
	-> output the args separated bu spaces, terminated with a newline (if -n is not indicated)
 	-> if set, the echo builtin expands backslash-escape sequences by default.

###	RETURN VALUE:
		0 if success
## [exit](https://www.geeksforgeeks.org/linux-unix/exit-command-in-linux-with-examples/)
	-> parameters:
		- without parameters: when executed `exit`, closes the current terminal session. When executed, the terminal will simply close.
		- specific status code: `exit [status]`the terminal will close and return the said status
		- exit a root sesion: (? este se implementa???
		- display help info: using `exit --help` it will display the help information for the exit command
###	RETURN VALUE:
		0 indicates no error
		1 encountered minor errors
		2 indicate the misuse of shell bultins
## [cd](https://www.ibm.com/docs/es/aix/7.3.0?topic=c-cd-command)
	-> uses the function [chdir](https://man7.org/linux/man-pages/man2/chdir.2.html)
	-> the `cd` command sets the current working directory of a process. The user must have execute (search) permission in the specified directory
 	-> if used without parameters, cd displays the current drive and directory.
   	-> if command extensions are enabled:
    	- the current directory string is converted to use the same case as the names on the disk. For example, cd c:\temp would set the current directory to C:\Temp if that is the case on the disk.
		- spaces aren't treated as delimiters, so <path> can contain spaces without enclosing quotation marks
###	RETURN VALUE:

## [pwd](https://www.geeksforgeeks.org/linux-unix/pwd-command-in-linux-with-examples/)
	-> uses the function [getcwd()](https://pubs.opengroup.org/onlinepubs/007904975/functions/getcwd.html)
	-> print the name of current/working directory on the standard output
    -> the getcwd() function shall fail if:
		[EINVAL] The size argument is 0.
		[ERANGE] The size argument is greater than 0, but is smaller than the length of the pathname +1.
		[EACCES] Read or search permission was denied for a component of the pathname.
		[ENOMEM] Insufficient storage space is available.-> uses the [getcwd](https://pubs.opengroup.org/onlinepubs/007904975/functions/getcwd.html) function
###	RETURN VALUE:
		0	in case getcwd doesn't fail
		>0	in case it does
		getcwd returns a NULL pointer in case of error or the buf argument in case of success.

## [unset]()
###	RETURN VALUE:

## [export]()
###	RETURN VALUE:

## [env]()
###	RETURN VALUE:

## ENVIROMENT VARIABLE
	### [env file](https://www.ibm.com/docs/es/aix/7.2.0?topic=files-env-file)
		The .env file is a system boot file which allows you to customize individual working environment variables
