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


// deberia ponerlo volatile sigatomic??
int	g_status;

// Data structures

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

#endif
