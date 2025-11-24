/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:10:10 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/24 16:37:31 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*	LIBRERIAS !	*/
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
# include "messages.h"

// Enums
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

// Data structures

typedef struct s_env
{
	char			*key;
	char			*value;
	int				visible;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	char	*user_input;
	int		pid;
}	t_shell;

typedef struct s_tokens_values
{
	char	*text;
	int		count;
	t_shell	*val;
}	t_tokens_values;

typedef struct s_process_vars
{
	t_quote_type	current_quote;
	int				i;
	int				sub_start;
	int				is_expanded;
}	t_process_vars;

typedef struct s_token	t_token;

typedef struct s_expand_data
{
	char			*content;
	t_token			**token;
	t_shell			*val;
	int				*index;
	int				*sub_start;
	t_quote_type	current_quote;
}	t_expand_data;

typedef struct s_redir
{
	t_token			*redir_content;
	t_redir_type	redir_type;
}	t_redir;

typedef struct s_token
{
	t_token			*left_side;
	t_token			*right_side;
	char			*content;
	t_token_type	type;
	t_redir			*redir;
}	t_token;

typedef struct s_cmd_table
{
	t_token	*token;
	char	**args;
}	t_cmd_table;

typedef struct s_values
{
	char	**args;
	t_token	*token;
	t_shell	*val_env;
	pid_t	*pids;
	int		index;
	int		cmds_size;
	int		status;
	int		fd_prev;
	int		fd_in;
	int		fd_out;
}	t_values;

// permite almacenar el estado de salida del ultimo
// comando ejecutado y expandir $?
volatile sig_atomic_t	g_status;

/*	Definiciones de funciones del proyecto	*/

t_env	*create_env_variable(char *key, char *value);
void	ft_setenv(t_shell *data, char *key, char *value);
void	already_exists(t_env *cpy, char *val);
char	*ft_getenv(const char *key, t_env *env);
char	**env_to_array(t_env *head);
void	free_node(t_env *node);
void	create_node(t_env *node, char *key, char *value, int state);
void	ft_lstclear_env(t_env **lst);
char	*ft_getkey(char *line, char *eq_pos);
char	*ft_getvalue(char *eq_pos);
t_env	*init_env(char **env);
void	handle_missing_env(t_shell *data, char *name);
int		bt_unset(t_shell *data, char **args);
int		bt_cd(char **args, t_values *data);
void	print_args(char **args, int start, int n_flag);
void	bt_echo(char **args);
int		bt_env(t_shell *data, char **args);
int		is_numeric(char *str);
int		bt_exit(t_shell *data, char **args);
int		bt_export(t_shell *data, char **args);
void	bt_pwd(t_shell *data);
void	free_data();
void	ft_free_double(char **arr);
void	ft_free_triple(char ***arr);
void	ft_free_double(char **arr);
void	ft_free_cmd_list(char ***list);
void	ft_free_vals(t_values *vals);
void	terminator(t_shell *data, int exit);
void	ft_here_doc(int *fd_in, const char *limiter);
int		ft_open_infile(t_token *token);
int		ft_open_outfile(t_token *token);
void	ft_set_infile(int *fd_write, const char *limiter);
int		ft_exec_args(char **args, t_shell *data);
void	debug_fd(int fd);
int		ft_exec_cmd_line(t_list *cmd_list, t_shell *data);
char	*ft_find_command_path(const char *cmd, t_shell *data);
int		ft_wait_children(int num_cmds, pid_t *pids);
int		ft_lexer(char *prompt);
void	ft_add_tokentolist(char *content, t_token *token);
t_list	*ft_build_cmd_table(t_list *tokens);
t_token	*ft_build_token(char *str_token);
t_quote_type	ft_check_quotes(char *token, t_quote_type t_type);
void	ft_expand_dolar(t_list **cmd_list, t_shell *data);
void	ft_expansion(t_expand_data *data);
void	ft_handle_env_var(t_expand_data *data, char **name, char *prev_str);
void	ft_remove_quotes(t_list *cmd_list);
t_list	*ft_split_tokens(char **tokens);
void	ft_first_expansion(char ****dolars_ex, char **word_split, int tokens_count);
void	ft_word_split(char *env_var, char *prev_content, t_token **token);
char	*ft_get_token(char *text);
char	**ft_tokenize(char *text);
int		ft_tokens_count(char *text);
void	ft_print_debug(t_list *cmd_list);
void	ft_print_args_debug(char **args);
void	ft_print_tokens_debug(t_token *token);
t_list	*ft_parse(char *prompt, t_shell *data);
int		minishell(int argc, char **argv, char **env);
void	loop(t_shell *data);
void	reset_prompt(int signo);
void	set_signals_interactive(void);
void	set_signals_handlers_exec(void);
int		print_sorted_env(t_env *env);
int		ft_is_redirection(char *s);
int		ft_isblank(int c);
int		ft_ismeta(int c);
int		ft_isspace(int c);
int		is_controlop(char *s);
int		is_filename(const char *s);
int		is_redop(char *s);
int		is_token(char *s);
int		is_word(char *s);
int		print_msg(char *function, char *msg, int exit);
void	print_prompt(void);
char	*prompt(void);
char	*handle_missing_user(void);
char	*handle_missing_path(void);
void	ft_free_split(char **split);

#endif
