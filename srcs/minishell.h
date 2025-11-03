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

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include "libft/libft.h"

# define TRUE 1
# define FALSE 0

typedef enum e_quote_type
{
	SIMPLE_QUOTES,
	DOUBLE_QUOTES,
	DEFAULT
}		t_quote_type;

typedef struct s_token	t_token;

typedef enum e_token_type
{
	REDIR,
	WORD
}		t_token_type;

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

typedef struct s_token
{
	t_token			*left_side;
	t_token			*right_side;
	char			*content;
	t_token_type	type;
	union
	{
		t_token			*redir_content;
		t_redir_type	redir_type;
	};
}	t_token;

typedef struct s_redirs	t_redirs;

typedef struct s_redirs
{
	t_token_type	type;
	char			*file;
	char			*limiter;
	t_redirs		*next;
	t_redirs		*before;
}				t_redirs;

typedef struct s_cmd_table
{
	t_token	*token;
	char	**args;
}				t_cmd_table;

typedef struct s_values
{
	char	**env;
	char	**tokens;
	char	***tokens_list;
	int		num_cmds;
	pid_t	*pids;
	int		status;
	int		fd_prev;
	int		fd_in;
	int		fd_out;
}				t_values;

typedef struct s_tokens_values
{
	char	*text;
	int		count;
}				t_tokens_values;

typedef struct s_dolar_extension
{
	int		token_len;
	char	*token_str;
}				t_dolar_extension;

typedef struct s_token_info
{
	char			*current_token;
	int				current_pos;
	int				start_dolar;
	t_quote_type	type;
}				t_token_info;

/*			LEXER				*/
int		ft_lexer(char *prompt);

/*			TOKENIZE			*/
char	**ft_tokenize(char *text);
char	*ft_get_token(char *text);
int		ft_tokens_count(char *text);
int		ft_isspace(char c);
int		ft_is_redirection(char *s);
int		ft_is_pipe(char *s);

/*			TRIM_QUOTES			*/
void	ft_trim_quotes(char **token, int token_len);
int		ft_contains_quotes(const char *text);
int		ft_quotes_count(char *token);
int		ft_count_simple_quote(char *token);

/*			EXTEND_DOLAR		*/
void	ft_extend_dolar(char *token, t_dolar_extension ***dolar_ext);

/*			CHANGE_DOLAR_VAL	*/
void	ft_change_dolar_val(char **token, t_dolar_extension **dolar_ext);
int		ft_token_expanded_len(char *token, t_dolar_extension **dolar_ext);

/*			HERE_DOC			 */
void	ft_here_doc(int *fd_in, const char *limiter);
void	ft_set_infile(int *fd_write, const char *limiter);
int		ft_open_infile(char ***args);
int		ft_open_outfile(char ***args);

/*			PARSE				*/
void	ft_parse(char *prompt, char **env);
char	***ft_command_list(t_values *vals);
void	ft_word_split(char *env_var, char *prev_content, t_token **token);
void	ft_add_tokentolist(char *content, t_token *token);
char	***ft_expand_dolar(char *tokens, char **env);
t_list	*ft_split_tokens(char **tokens);
t_token	*ft_build_token(char *str_token);
t_quote_type	ft_check_quotes(char *token, t_quote_type t_type);
t_list	*ft_build_cmd_table(t_list *tokens);

/*			GET_ENV				*/
char	*ft_getenv(const char *name, char **env);

/*			EXEC_CMD			*/
void	ft_exec_cmd_line(t_values *vals);
int		ft_exec_args(char **args, char **env);
char	*ft_find_command_path(const char *cmd, char **env);

/*			FREE_MEMORY			 */
void	ft_free_triple(char ***arr);
void	ft_free_double(char **arr);
void	ft_free_cmd_list(char ***list);
void	ft_free_vals(t_values *vals);

/*			UTILS				 */
int		ft_double_arr_size(char **arr);
int		ft_triple_arr_size(char ***arr);
int		ft_count_arr(char ***tokens);
char	**ft_dup_tokens(char **tokens);
int		ft_isvalid_envvar(char *name, char **env);

#endif
