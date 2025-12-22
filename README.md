<div align=center>
<h1 align="center">Minishell</h1>
<h2>Alex & Violeta</h2>
--- 

<div align=center>
<h1 align="center">Project Functions</h1>
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

<img align=center src="https://github.com/violetatatatatatatata/minishell/blob/main/image.png">
