/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:10:10 by avelandr          #+#    #+#             */
/*   Updated: 2025/12/18 17:37:49 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*	LIBRERIAS
 *	*/
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

// terminal y entorno
# include <termios.h>
# include <sys/ioctl.h>
# include <termcap.h>

// archivos y directorios
# include <dirent.h>
# include <sys/stat.h>

// senyales
# include <signal.h>

// readline
# include <readline/readline.h>
# include <readline/history.h>

// implemented
# include "../libft/Includes/libft.h"
# include "colors.h"

/*	DEFINES
 * */
# define TRUE 1
# define FALSE 0
# define MAX_LONG "9223372036854775807"
# define DIR_FAILED "Error: No such file or directory"
# define HOME_FAILED "HOME not set"
# define NOT_INFILE_MSG "no such file or directory"
# define NOT_CMD_MSG "command not found"
# define NOT_PERMISSION_MSG "permission denied"

extern volatile sig_atomic_t	g_status;

/*	ENUMS
 * */
typedef enum e_quote_type
{
	SIMPLE_QUOTES,
	DOUBLE_QUOTES,
	DEFAULT
}		t_quote_type;

typedef enum e_token_type
{
	REDIR,
	WORD
}			t_token_type;

typedef enum e_redir_type
{
	APPEND,
	HEREDOC,
	INPUT,
	OUTPUT
}		t_redir_type;

typedef enum e_cmd_type
{
	COMMAND,
	ARGS,
	REDIRS,
	INDEX,
	HEREDOC_NAME
}		t_cmd_type;

/*	DATA STRUCTURES
 * */
typedef struct s_env
{
	char			*key;
	char			*value;
	int				visible;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env			*env;
	char			*user_input;
	int				exit_status;
}	t_shell;

typedef struct s_tokens_values
{
	char			*text;
	int				count;
	t_shell			*val;
}	t_tokens_values;

typedef struct s_process_vars
{
	t_quote_type	current_quote;
	int				i;
	int				sub_start;
	int				is_expanded;
}	t_process_vars;

typedef struct s_expand_data
{
	char			*content;
	t_token			**token;
	t_shell			*val;
	int				*index;
	int				*sub_start;
	t_quote_type	current_quote;
	int				*exit_status;
}	t_expand_data;

typedef struct s_redir
{
	t_token			*redir_content;
	t_redir_type	redir_type;
}	t_redir;

struct s_token
{
	t_token			*left_side;
	t_token			*right_side;
	char			*content;
	t_token_type	type;
	t_redir			*redir;
};

typedef struct s_cmd_table
{
	t_token			*token;
	char			**args;
}	t_cmd_table;

typedef struct s_values
{
	char			**args;
	t_token			*token;
	t_shell			*val_env;
	pid_t			*pids;
	t_list			*cmd_list;
	int				**pipes;
	int				index;
	int				cmds_size;
	int				status;
	int				fd_prev;
	int				fd_in;
	int				fd_out;
	int				exit_val;
}	t_values;

int				sort_pass(t_env *list);
int				bt_unset(t_shell *data, char **args);
int				bt_cd(char **args, t_values *data);
int				bt_env(t_shell *data, char **args);
int				is_numeric(char *str);
int				bt_exit(t_shell *data, char **args, t_list *table_lst);
int				bt_export(t_shell *data, char **args);
int				ft_here_doc(int *fd_in, const char *limiter);
int				ft_open_infile(t_token *token, int *ret_val);
int				ft_open_outfile(t_token *token, int *ret_val);
int				ft_set_infile(int *fd_write, const char *limiter);
int				ft_exec_args(t_values *vals, t_shell *data);
int				ft_exec_builtin(t_values *data, t_shell *shell);
int				ft_exec_cmd_line(t_list *cmd_list, t_shell *data);
int				ft_wait_children(int num_cmds, pid_t *pids);
int				ft_wait_fork(pid_t pid);
int				ft_set_pipes(t_values *vals);
int				ft_lexer(char *prompt);
int				ft_tokens_count(char *text);
int				ft_args_count(t_token *token);
int				minishell(int argc, char **argv, char **env);
int				ft_is_buitlin(char *s);
int				ft_is_redirection(char *s);
int				ft_isblank(int c);
int				ft_ismeta(int c);
int				ft_isspace(int c);
int				is_controlop(char *s);
int				is_filename(const char *s);
int				is_redop(char *s);
int				is_token(char *s);
int				is_word(char *s);
int				ft_is_pipe(char *s);
int				ft_double_arr_size(char **arr);
int				print_msg(char *function, char *msg, int exit);
void			ft_setenv(t_shell *data, char *key, char *value);
void			already_exists(t_env *cpy, char *val);
void			free_node(t_env *node);
void			create_node(t_env *node, char *key, char *value, int state);
void			ft_lstclear_env(t_env **lst);
void			handle_missing_env(t_shell *data, char *name);
void			print_args(char **args, int start, int n_flag);
void			bt_echo(char **args);
void			bt_pwd(t_shell *data);
void			free_data(void);
void			ft_free_double(char **arr);
void			ft_free_triple(char ***arr);
void			ft_free_cmd_list(t_cmd_table *table);
void			ft_free_vals(t_values *vals, int exit_status, int is_exit);
void			terminator(t_shell *data, int exit_status, int is_exit);
void			ft_free_split(char **split);
void			free_cmd(void *content);
void			ft_expand_red(t_list *cmd_list, t_shell *data);
void			debug_fd(int fd);
void			ft_free_pipes(t_values *vals, int size);
void			ft_close_pipes(t_values *vals);
void			ft_last_cmd(t_values *vals);
void			ft_command_loop(t_values *vals);
void			ft_add_tokentolist(char *content, t_token *token);
void			ft_expand_dolar(t_list **cmd_list, t_shell *data);
void			ft_expansion(t_expand_data *data);
void			ft_handle_env_var(t_expand_data *data, char **name,
					char *prev_str);
void			ft_remove_quotes(t_list *cmd_list);
void			ft_first_expansion(char ****dolars_ex, char **word_split,
					int tokens_count);
void			ft_word_split(char *env_var, char *prev_content,
					t_token **token);
void			ft_insert_exit_value(t_expand_data *data, int val,
					char *prev_str);
void			ft_insert_env_value(t_expand_data *data, char *env_var,
					char *prev_str);
void			ft_expand_token_list(t_token *token, t_shell *data);
void			ft_process_token_list(t_token *token);
void			ft_print_debug(t_list *cmd_list);
void			ft_print_args_debug(char **args);
void			ft_print_tokens_debug(t_token *token);
void			loop(t_shell *data);
void			reset_prompt(int signo);
void			set_signals_int(void);
void			set_signals_handlers_exec(void);
void			signals_heredoc(void);
void			print_prompt(void);
char			*ft_getenv(char *key, t_env *env);
char			**env_to_array(t_env *head);
char			*ft_getkey(char *line, char *eq_pos);
char			*ft_getvalue(char *eq_pos);
char			*ft_find_command_path(char *cmd, t_shell *data);
char			*ft_get_token(char *text);
char			**ft_tokenize(char *text);
char			*prompt(t_shell *data);
char			*handle_missing_user(void);
char			*handle_missing_path(void);
t_env			*create_env_variable(char *key, char *value);
t_env			*init_env(char **env);
t_env			*dupe_env(t_env *env);
t_list			*ft_build_cmd_table(t_list *tokens);
t_token			*ft_build_token(char *str_token);
t_quote_type	ft_check_quotes(char *token, t_quote_type t_type);
t_list			*ft_split_tokens(char **tokens);
t_list			*ft_parse(char *prompt, t_shell *data);
long			print_sorted_env(t_env *env);

#endif
