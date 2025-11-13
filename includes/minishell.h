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

#define TRUE 0
#define	FALSE 1

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
typedef struct s_shell
{
	t_env	**env;
	char	*user_input;
	int		pid;
	int		interactive;
} t_shell;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				visible;
	struct s_env	*next
} t_env

typedef struct s_tokens_values
{
	char	*text;
	t_values	*val;
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
	t_values		*val;
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
}				t_cmd_table;

typedef struct s_values
{
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

volatile sigatomic	g_status;

/*	Definiciones de funciones del proyecto	*/

// is_definition
int	ft_isblank(int c);
int	ft_ismeta(int c);
int	is_controlop(const char *str);
int	ft_isspace(int c);
int	is_controlop(const char *str);
int	is_filename(const char *s);
int	is_redop(const char *str);
int	is_token(const char *str);
int	is_word(const char *s);

// builtins

#endif
