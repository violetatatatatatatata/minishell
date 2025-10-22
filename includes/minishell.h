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
# include "libft.h"

// Terminal y entorno
# include <termios.h>
# include <sys/ioctl.h>
# include <termcap.h>

// Archivos y directorios
# include <dirent.h>
# include <sys/stat.h>

// Senyales
# include <signal.h>

// Readline
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/Includes/libft.h"
# include "colors.h"

// Macros
# define	TRUE 1
# define	FALSE 0

// deberia ponerlo volatile sigatomic??
int	g_status;

// definir mensajes de error
# define INPUT_ERROR "ponermensajeaqui"

// mensajes de ejecucion
# define PROMPT ">>> shelly: "

// Data structures
typedef struct	s_data
{
	int			is_interactive;
//	t_token		*token;
	char		*user_input;
	char		**env;
	char		*working_dir;
	char		*old_working_dir;
//	t_command	*cmd;
	pid_t		pid;
}	t_data;

/*	Definiciones de funciones del proyecto	*/

void    print_msg(char *msg, int *exit);

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
void	enver(char**environ);

// PARSER
// execution.c
int		check_execution(t_data *data, int argc, char **argv);
// parse_input.c
void	parse_input();

//Pipex
typedef signed int	t_pid;
char	*getenvar(char *name, char **env);
char	*my_getenv(char *name, char **env);
void	cierra(int in, int out);
void	finish(int error);
void	ft_free_pointstring(char **tab);
void	doblefree(char **a, char **b);
int		checkacces(char **s_cmd, char **allpath, char **exec);
int		notempty(char **a, char **b);

// EXECUTE
void	execute();
// interactive
void	reset_prompt(int signo);
void	exect_interactive(t_data *data);
// noninteractive
void	exectscript(t_data *data);
void	exect_noninteractive(t_data *data, int argc, char **argv);
void	non_interactive(t_data *data, int argc, char **argv);

// TERMINATOR
void	free_data();
// void	exit_shelly();

#endif
