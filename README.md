<div align=center>
<h1 align="center">Minishell</h1>
<h2>Alex & Violeta</h2>
--- 

<div align=center>
<h1 align="center">Project Functions</h1>
<h2 align="center">Allowed Functions</h2>
| Function				| Manual Page		| From lib			| Description
| :--					| :--				| :--				| :--
| **printf**			| `man 3 printf`	| `<stdio.h>`		| write output to stdout
| **malloc**			| `man malloc`		| `<stdlib.h>`		| allocate dynamic memory
| **free**				| `man 3 free`		| `<stdlib.h>`		| free dynamic memory
| **read**				| `man 2 read`		| `<unistd.h>`		| read from a file descriptor
| **write**				| `man 2 write`		| `<unistd.h>`		| write to a file descriptor
| **open**				| `man 2 open`		| `<fcntl.h>`		| open and possibly create a file
| **close**				| `man 2 open`		| `<unistd.h>`		| close a file descriptor
| **fork**				| `man fork`		| `<unistd.h>`		| create a child process
| **wait**				| `man wait`		| `<sys/wait.h>`	| wait for process to change state
| **waitpid**			| `man waitpid`		| `<sys/wait.h>`	| wait for process to change state
| **exit**				| `man exit`		| `<stdlib.h>`		| cause normal process termination
| **execve**			| `man execve`		| `<unistd.h>`		| execute program
| **dup**				| `man dup`			| `<unistd.h>`		| duplicate a file descriptor
| **dup2**				| `man dup2`		| `<unistd.h>`		| duplicate a file descriptor
| **pipe**				| `man pipe`		| `<unistd.h>`		| create pipe
| **strerror**			| `man strerror`	| `<string.h>`		| return string describing error number
| **errno**				| `man errno`		| `<errno.h>`		| number of last error
| **access**			| `man access`		| `<unistd.h>`		| checks the access permissions
| **perror**			| `man perror`		| `<stdio.h>`		| look up the error message string corresponding to an error
| **getenv**			|					|					| getting the value of variables from the env list
| **wait3**				| `man wait3`		| `<sys/wait.h>`	| (obsolete) wait for process to change state, BSD style
| **wait4**				| `man wait4`		| `<sys/wait.h>`	| (obsolete) wait for process to change state, BSD style
| **signal**			| `man signal`		| `<signal.h>`		| ANSI C signal handling
| **kill**				| `man 2 kill`		| `<signal.h>`		| send signal to a process
| **getcwd**			| `man getcwd`		| `<unistd.h>`		| get current working directory
| **chdir**				| `man chdir`		| `<unistd.h>`		| change working directory
| **stat**				| `man 2 stat`		| `<sys/stat.h>`	| get file status by pathname
| **lstat**				| `man lstat`		| `<sys/stat.h>`	| get file status by pathname (for symlinks)
| **fstat**				| `man fstat`		| `<sys/stat.h>`	| get file status by fd
| **opendir**			| `man opendir`		| `<dirent.h>`		| open a directory
| **readdir**			| `man readdir`		| `<dirent.h>`		| read a directory
| **closedir**			| `man closedir`	| `<dirent.h>`		| close a directory
| **isatty**			| `man isatty`		| `<unistd.h>`		| determines if the file descriptor fd refers to a valid terminal
| **ttyname**			| `man ttyname`		| `<unistd.h>`		| gets the related device name of a file descriptor for which isatty() is true
| **ttyslot**			| `man ttyslot`		| `<unistd.h>`		| returns the name stored in a static buffer which will be overwritten on subsequent calls
| **ioctl**				| `man ioctl`		| `<sys/ioctl.h>`	| manipulates the underlying device parameters of special files
| **unlink**			| `man unlink`		| `<unistd.h>`		| deletes a name from the filesystem
| **sigaction**			| `man sigaction`	| `<signal.h>`		| assigns an action for a signal specified by sig
| **sigemptyset**		| `man sigemptyset`	| `<signal.h>`		| initializes a signal set to be empty
| **sigaddset**			| `man sigaddset`	| `<signal.h>`		| adds the specified signal signo to the signal set
| **tcsetattr**			| `man tcsetattr`	| `<termios.h>`		| setting the termios structure
| **tcgetattr**			| `man tcgetattr`	| `<termios.h>`		| getting the termios structure
| **tgetent**			| `man tgetent`		| `<curses.h>` `<term.h>`| loads the entry for name
| **tgetflag**			| `man tgetflag`	| `<curses.h>` `<term.h>`| gets the boolean entry for id, or zero if it is not available
| **tgetnum**			| `man tgetnum`		| `<curses.h>` `<term.h>`| gets the numeric entry for id, or -1 if it is not available
| **tgetstr**			| `man tgetstr`		| `<curses.h>` `<term.h>`| returns the string entry for id, or zero if it is not available
| **tgoto**				| `man tgoto`		| `<curses.h>` `<term.h>`| instantiates the parameters into the given capability
| **tputs**				| `man tputs`		| `<curses.h>` `<term.h>`| applies  padding  information  to the string str and outputs it
| **readline**			| 					| `<stdio.h>` `<readline/readline.h>` `<readline/history.h>`| will read a line from the terminal and return it, using prompt as a prompt
| **rl_clear_history**	| 					| `<stdio.h>` `<readline/readline.h>` `<readline/history.h>`| Clear the history list by deleting all of the entries
| **rl_on_new_line**	| 					| `<stdio.h>` `<readline/readline.h>` `<readline/history.h>`| Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline
| **rl_replace_line**	| 					| `<stdio.h>` `<readline/readline.h>` `<readline/history.h>`| Replace the contents of rl_line_buffer with text
| **rl_redisplay**		| 					| `<stdio.h>` `<readline/readline.h>` `<readline/history.h>`| Change what’s displayed on the screen to reflect the current contents of rl_line_buffer
| **add_history**		|					| `<stdio.h>` `<readline/readline.h>` `<readline/history.h>`| Saving the line into the history

<div align=center>
<h2>Core Implementation</h2>

### Builtins
| Function | File Path | Description |
| :-- | :-- | :-- |
| **bt_cd** | `srcs/builtins/cd.c` | Changes the current working directory and updates PWD/OLDPWD. |
| **bt_echo** | `srcs/builtins/echo.c` | Outputs strings to stdout with optional `-n` flag support. |
| **bt_env** | `srcs/builtins/env.c` | Prints the current environment variables marked as visible. |
| **bt_exit** | `srcs/builtins/exit.c` | Terminates the shell with a specific numeric status and cleans memory. |
| **bt_export** | `srcs/builtins/export.c` | Adds or updates environment variables in the custom env list. |
| **bt_pwd** | `srcs/builtins/pwd.c` | Prints the absolute path of the current working directory. |
| **bt_unset** | `srcs/builtins/unset.c` | Removes a variable from the environment list. |

### Environment
| Function | File Path | Description |
| :-- | :-- | :-- |
| **init_env** | `srcs/env/init_env.c` | Converts the system `char **env` into a custom linked list. |
| **ft_getenv** | `srcs/env/env_setandget.c` | Searches and returns the value of a specific key in the env list. |
| **ft_setenv** | `srcs/env/env_setandget.c` | Updates or creates a new node in the environment list. |
| **env_to_array** | `srcs/env/env_to_array.c` | Converts the linked list back to a `char **` for `execve`. |

### Execution
| Function | File Path | Description |
| :-- | :-- | :-- |
| **ft_exec_cmd_line**| `srcs/execute/ft_exec_cmd_line.c` | Main execution loop that iterates through the command table. |
| **ft_exec_builtin** | `srcs/execute/ft_exec_builtin.c` | Dispatches execution to the corresponding internal builtin function. |
| **ft_find_command_path** | `srcs/execute/ft_find_command_path.c` | Searches the `PATH` variable to find the binary's absolute path. |
| **ft_set_pipes** | `srcs/execute/ft_set_pipes.c` | Initializes the file descriptors for inter-process communication. |
| **ft_wait_children** | `srcs/execute/ft_wait_children.c` | Waits for all forked processes and updates the global status. |

### Parsing & Lexing
| Function | File Path | Description |
| :-- | :-- | :-- |
| **ft_lexer** | `srcs/lexer/ft_lexer.c` | Performs initial syntax validation (pipes, quotes, redirections). |
| **ft_parse** | `srcs/parser/ft_parse.c` | Orchestrates the transformation from raw input to command structures. |
| **ft_tokenize** | `srcs/parser/tokenize/...` | Breaks the input string into a list of meaningful raw tokens. |
| **ft_expand_dolar** | `srcs/parser/ft_expand_dolar.c` | Handles variable expansion ($VAR) and exit status expansion ($?). |
| **ft_remove_quotes** | `srcs/parser/ft_remove_quotes.c` | Cleans the tokens by removing unnecessary ' and " characters. |
| **ft_build_cmd_table**| `srcs/parser/ft_build_cmd_table.c` | Organizes tokens into commands, arguments, and redirections. |

### File Descriptors & Redirections
| Function | File Path | Description |
| :-- | :-- | :-- |
| **ft_here_doc** | `srcs/fd_files/ft_here_doc.c` | Manages the `<<` input redirection until the delimiter is found. |
| **ft_open_infile** | `srcs/fd_files/ft_open_infile.c` | Opens and validates the input files for a specific command. |
| **ft_open_outfile** | `srcs/fd_files/ft_open_outfile.c` | Handles `>` and `>>` by opening or creating files. |

### Lifecycle & Terminator
| Function | File Path | Description |
| :-- | :-- | :-- |
| **minishell** | `srcs/init/minishell.c` | Main initialization function that sets up the environment. |
| **shell_loop** | `srcs/init/shell_loop.c` | The main interactive loop (Readline -> Lexer -> Parse -> Exec). |
| **terminator** | `srcs/terminator/terminator.c` | Centralized exit point that ensures no memory leaks on shutdown. |
| **ft_free_cmd_list** | `srcs/terminator/ft_free_cmd_list.c`| Specialized deep-free of the command table and its tokens. |

</div>
| **ft_
