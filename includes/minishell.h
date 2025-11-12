/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:55 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:58 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*	LIBRERIAS !	*/
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

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
# include "../libft/libft.h"
//# include "../libft/Includes/libft.h"
# include "colors.h"
# include "messages.h"

// deberia ponerlo volatile sigatomic??
//int						g_status;

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
typedef struct s_tokens_values
{
	char	*text;
	char	**env;
	int		count;
}				t_tokens_values;

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
	int				*index;
	int				*sub_start;
	t_quote_type	current_quote;
	char			**env;
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
}				t_cmd_table;

typedef struct s_values
{
	char	**env;
	char	**args;
	t_token	*token;
	pid_t	*pids;
	int		index;
	int		cmds_size;
	int		status;
	int		fd_prev;
	int		fd_in;
	int		fd_out;
}				t_values;

// builtins

/*			LEXER				*/
int				ft_lexer(char *prompt);

/*			TOKENIZE			*/
char			**ft_tokenize(char *text);
char			*ft_get_token(char *text);
int				ft_tokens_count(char *text);
int				ft_is_redirection(char *s);
int				ft_is_pipe(char *s);

/*			HERE_DOC			 */
void			ft_here_doc(int *fd_in, const char *limiter);
void			ft_set_infile(int *fd_write, const char *limiter);
int				ft_open_infile(t_token *token);
int				ft_open_outfile(t_token *token);

/*			PARSE				*/
t_list			*ft_parse(char *prompt, char **env);
void			ft_word_split(char *env_var, char *prev_content,
					t_token **token);
void			ft_add_tokentolist(char *content, t_token *token);
void			ft_expand_dolar(t_list **cmd_list, char **env);
void			ft_expansion(t_expand_data *data);
void			ft_handle_env_var(t_expand_data *data, char **name,
					char *prev_str);
t_list			*ft_split_tokens(char **tokens);
t_token			*ft_build_token(char *str_token);
t_quote_type	ft_check_quotes(char *token, t_quote_type t_type);
t_list			*ft_build_cmd_table(t_list *tokens);
void			ft_remove_quotes(t_list *cmd_list);

/*			GET_ENV				*/
char			*ft_getenv(const char *name, char **env);

/*			EXEC_CMD			*/
void			ft_exec_cmd_line(t_list *cmd_list, char **env);
int				ft_exec_args(char **args, char **env);
char			*ft_find_command_path(const char *cmd, char **env);
int				ft_wait_children(int num_cmds, pid_t *pids);

/*			FREE_MEMORY			 */
void			ft_free_triple(char ***arr);
void			ft_free_double(char **arr);
void			ft_free_cmd_list(char ***list);
void			ft_free_vals(t_values *vals);

/*			UTILS				 */
int				ft_double_arr_size(char **arr);
int				ft_triple_arr_size(char ***arr);
int				ft_count_arr(char ***tokens);
char			**ft_dup_tokens(char **tokens);
int				ft_isvalid_envvar(char *name, char **env);

/*	Definiciones de funciones del proyecto	*/
void			print_msg(char *msg, int *exit);

// is_definition
int				ft_isblank(int c);
int				ft_ismeta(int c);
int				is_controlop(const char *str);
int				ft_isspace(int c);
int				is_controlop(const char *str);
int				is_filename(const char *s);
int				is_redop(const char *str);
int				is_token(const char *str);
int				is_word(const char *s);
int				ft_is_pipe(char *s);
int				ft_is_redirection(char *s);

#endif
