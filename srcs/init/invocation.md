# MAIN LOOP

## 1. Initialization (`minishell`)
Before entering the main loop, the shell prepares its internal state.

* **Environment Setup**:
    * The shell receives `char **envp` from `main`. If it is empty, creates a basic enviroment with '_', 'PWD' and 'SHLVL'
    * It converts this array into a linked list (`t_env`) for easier manipulation.
    * **SHLVL**: Increments the `SHLVL` variable (or creates it set to `1` if missing).
    * **PWD/OLDPWD**: Ensures these variables are set correctly based on the current directory.
* **Signal Handlers**: Configures the initial signal traps (`SIGINT`, `SIGQUIT`) to behave like a shell (e.g., creating a new prompt line on `Ctrl+C`).

## 2. The Main Loop (`loop`)
Located in `srcs/init/shell_loop.c`, this function runs indefinitely until the shell exits. Each iteration represents one command cycle.

### Step 1: Read Input
* **Prompt**: Displays the prompt (e.g., `user@minishell$ `) using `readline()`.
* **History**: If the input is not empty, it is added to the history using `add_history()`.
* **EOF (Ctrl+D)**: If `readline` returns `NULL`, the shell prints `exit`, frees resources, and terminates execution.

### Step 2: Lexer / Validation (`ft_lexer`)
Before processing the input, the shell performs a syntax check to ensure the quotes and pipes are closed.

* Checks for unclosed quotes (`'` or `"`).
* Checks for invalid pipe placement (e.g., `| cmd`, `cmd |`, or `||`).
* *Error Handling*: If a syntax error is detected, an error message is printed, the exit status is updated, and the loop restarts (skipping execution).

### Step 3: Parsing (`ft_parse`)
Transforms the raw string input into a structured list of commands ready for execution.

1.  **Tokenization**: Splits the input string into tokens (words, operators, redirection symbols) while respecting quotes.
2.  **Expansion**: Expands environment variables (`$VAR`) and handles `$?`.
3.  **Quote Removal**: Strips the outer quotes from the tokens after expansion.
4.  **Command Table Creation**: Groups tokens into `t_cmd_table` structures. Each node in the list represents one command in a pipeline.
    * *Example*: `ls -l | grep .c` becomes a list of two nodes.

### Step 4: Execution (`ft_exec_cmd_line`)
The structured command list is passed to the execution engine.

* **Signal Update**: Before execution, signal handlers are updated to ignore `SIGINT`/`SIGQUIT` in the parent process (so only the child processes handle them).
* **Pipeline Execution**: The shell forks processes and sets up pipes/redirections as described in the **Execution Module**.
* **Waiting**: The parent waits for the pipeline to finish and collects the exit status.
* **Signal Restore**: After execution, signals are reset to interactive mode (prompt mode).

### Step 5: Cleanup & Reset
At the end of each iteration, temporary resources are freed to prevent memory leaks.

* The command list (`t_list`) and its contents are freed.
* The raw input string from `readline` is freed.
* The shell creates a new prompt line and waits for the next input.

## Termination
The shell exits the loop only under specific conditions:
* **Interactive**: The user presses `Ctrl+D` (sending EOF to `readline`).
* **Command**: The user executes the `exit` builtin.

In both cases, `free_data()` is called to clean up the environment list and global structures before returning the final exit code to the operating system.
