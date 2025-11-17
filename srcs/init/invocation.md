# INVOCATION

# ENV
	SHLVL: nivel de bash que te encuentras
## Algorithm
- Allocate memory for the main struct
- Print the first prompt
- Init the main struct
- First parse check: number of arguments

## Interactive mode
An interactive shell is one started without non-option arguments (unless -s is
specified) and without the -c option whose standard input and error are both
connected to terminals (as determined by isatty(3)), or one started with the -i
option.
	   
### how bash executes its startup files
If	any  of the	files  exist but cannot be read, bash reports an error.
Tildes are expanded in filenames as described below under Tilde Expansion
in the EXPANSION section.

- When bash is invoked as an interactive login shell,	itfirst reads and
executes commands from the file /etc/profile, if that file exists.
- After reading that file, it looks for `~/.bash_profile`, `~/.bash_login`,
and `~/.profile`, in that order, and reads and executes commands from the first
one that exists and is readable.

When an interactive login shell exits, or a non-interactive login shell executes
the exit builtin command, bash reads and executes commands from the file
`~/.bash_logout`, if it exists.

## Non-Interactive mode
When bash is started non-interactively, to run a shell script, for example, it
looks for the variable `BASH_ENV` in the environment, expands its value if it
appears there, and uses the expanded value as the name of a file to read and
execute.

### Bash behaves as if the following command were executed:
	if [ -n "$BASH_ENV" ];
		then . "$BASH_ENV"; fi
	but the value of the PATH variable is not used to search for the filename.
When invoked as an interactive shell with the name sh,  bash looks  for  the
variable  ENV, expands its value if it is defined, and uses the expanded value
as the name of a file to read and execute.
Since a shell invoked as sh does  not  attempt  to  read  and execute commands
from any other startup files, the --rcfile option has no effect.

# SIGNALS
 When bash is interactive, in the absence of any traps, it ignores SIGTERM
 (so that kill 0 does not kill an interactive shell), and SIGINT is caught and
 handled (so that the  wait builtin is interruptible).
 In all cases, bash ignores SIGQUIT.  

 Non-builtin  commands  run by bash have signal handlers set to the values
 inherited by the shell from its parent.  When job control is not in effect,
 asynchronous commands ignore SIGINT and SIGQUIT in addition to these inherited
 handlers.
 
 If bash is waiting for a command to complete and receives a signal for which a
 trap has been set, the trap will not be executed until the command completes.
 When bash is waiting for an asynchronous command via the wait builtin, the
 reception of a signal for which a trap has been set will cause the wait builtin
 to return immediately with  an  exit  status greater than 128, immediately
 after which the trap is executed.


