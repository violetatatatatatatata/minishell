# BUILTINS
## [echo](https://www.ibm.com/docs/es/aix/7.2.0?topic=e-echo-command)
	- output the args separated bu spaces, terminated with a newline (if -n is not indicated)
 	- if set, the echo builtin expands backslash-escape sequences by default.

###	RETURN VALUE:
		0 if success
		1 else
## [exit](https://www.geeksforgeeks.org/linux-unix/exit-command-in-linux-with-examples/)
	- parameters:
		- without parameters: when executed `exit`, closes the current terminal session. When executed, the terminal will simply close.
		- specific status code: `exit [status]`the terminal will close and return the said status
		- when called, the [exit](https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-exit-end-program) function in C performs the following operations:
			- flushes unwritten buffered data.
			- closes all open files.
			- removes temporary files.
			- returns an integer exit status to the operating system.
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

### BEHAVIOR
 	1. If *no directory* operand is given and the HOME environment
		variable is empty or undefined, the default behavior is
		implementation-defined and no further steps shall be taken.

	2. If *no directory* operand is given and the HOME environment
		variable is set to a non-empty value, the cd utility shall
		behave as if the directory named in the HOME environment
		variable was specified as the directory operand.

	4. If the first component of the directory operand is dot or dot-
		dot, proceed to step 6.

	5. Starting with the first pathname in the <colon>-separated
		pathnames of CDPATH (see the ENVIRONMENT VARIABLES section) if
		the pathname is non-null, test if the concatenation of that
		pathname, a 'slash' character if that pathname did not end
		with a 'slash' character, and the directory operand names a
		directory. If the pathname is null, test if the concatenation
		of dot, a 'slash' character, and the operand names a
		directory. In either case, if the resulting string names an
		existing directory, set curpath to that string and proceed to
		step 7. Otherwise, repeat this step with the next pathname in
		CDPATH until all pathnames have been tested.

	6. Set curpath to the directory operand.

	8. The curpath value shall then be converted to canonical form as
		follows, considering each component from beginning to end, in
		sequence:

		 a. Dot components and any 'slash' characters that separate
			them from the next component shall be deleted.

		 b. For each dot-dot component, if there is a preceding
			component and it is neither root nor dot-dot, then:

		i.  If the preceding component does not refer (in the
			 context of pathname resolution with symbolic links
			 followed) to a directory, then the cd utility shall
			 display an appropriate error message and no further
			 steps shall be taken.

			ii.  The preceding component, all 'slash' characters
			 separating the preceding component from dot-dot, dot-
			 dot, and all 'slash' characters separating dot-dot
			 from the following component (if any) shall be
			 deleted.

		 c. An implementation may further simplify curpath by removing
			any trailing 'slash' characters that are not also leading
			'slash' characters, replacing multiple non-leading
			consecutive 'slash' characters with a single 'slash', and
			replacing three or more leading 'slash' characters with a
			single 'slash'.  If, as a result of this canonicalization,
			the curpath variable is null, no further steps shall be
			taken.

	9. 	If curpath is longer than {PATH_MAX} bytes (including the
		terminating null) and the directory operand was not longer
		than {PATH_MAX} bytes (including the terminating null), then
		curpath shall be converted from an absolute pathname to an
		equivalent relative pathname if possible. This conversion
		shall always be considered possible if the value of PWD, with
		a trailing 'slash' added if it does not already have one, is
		an initial substring of curpath.  Whether or not it is
		considered possible under other circumstances is unspecified.
		Implementations may also apply this conversion if curpath is
		not longer than {PATH_MAX} bytes or the directory operand was
		longer than {PATH_MAX} bytes.

		10. The cd utility shall then perform actions equivalent to the
		chdir() function called with curpath as the path argument. If
		these actions fail for any reason, the cd utility shall
		display an appropriate error message and the remainder of this
		step shall not be executed. If the -P option is not in effect,
		the PWD environment variable shall be set to the value that
		curpath had on entry to step 9 (i.e., before conversion to a
		relative pathname). If the -P option is in effect, the PWD
		environment variable shall be set to the string that would be
		output by pwd -P.  If there is insufficient permission on the
		new directory, or on any parent of that directory, to
		determine the current working directory, the value of the PWD
		environment variable is unspecified.

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

## [unset]()
###	RETURN VALUE:

## [export](https://www.geeksforgeeks.org/linux-unix/export-command-in-linux-with-examples/)
	- It allows variables to be available in the current shell session and any child processes, which helps in setting up and configuring your shell environment dynamically.
	-  The shell shall format the output, including the proper use of
       quoting, so that it is suitable for reinput to the shell as
       commands that achieve the same exporting results, except:
        1. Read-only variables with values cannot be reset.
        2. Variables that were unset at the time they were output need
           not be reset to the unset state if a value is assigned to the
           variable between the time the state was saved and the time at
           which the saved output is reinput to the shell.
       When no arguments are given, the results are unspecified.

###	RETURN VALUE:

## [env]()
###	RETURN VALUE:

## ENVIROMENT VARIABLE
	### [env file](https://www.ibm.com/docs/es/aix/7.2.0?topic=files-env-file)
		The .env file is a system boot file which allows you to customize individual working environment variables
