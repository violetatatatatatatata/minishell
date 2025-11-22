#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_get_next_line_var
{
	char			buffer[BUFFER_SIZE + 1];
	int				bytes_read;
	char			*temp_str;
	char			*str;
}	t_get_next_line_var;

int				ft_atoi(const char *n);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nelem, size_t elsize);
//Compares
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
//Memory
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t c);
void			*ft_memmove(void *dest, const void *src, size_t c);
void			*ft_memset(void *dest, int c, size_t count);
//File descriptors
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int num, int fd);
void			ft_putstr_fd(char const *s, int fd);
//Arrays
int				ft_count_if(char **tab, int (*f)(char*));
void			ft_foreach(int *tab, int length, void (*f)(int));
int				*ft_range(int min, int max);
//Strings
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strdup(const char *s);
size_t			ft_strlcat(char *dest, char *src, size_t size);
size_t			ft_strlcpy(char *dest, char *src, size_t size);
size_t			ft_strlen(const char *str);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);
int				ft_tolower(int str);
int				ft_toupper(int str);
void			ft_striteri(char *s, void (*f)(unsigned int i, char *s));
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_itoa(int n);
char			**ft_split(char const *s, char c);
int				ft_strcmp(char *s1, char *s2);
//listas
int				ft_lstsize(t_list *lst);
t_list			*ft_lstnew(void *content);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstalast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
t_list			\
*ft_lstmap(t_list *lst, void *(*f)(void *),	void (*del)(void *));
//get_next_line
char			*get_next_line(int fd);
int				ft_read_loop(int fd, char *buffer, char **temp_str);
char			*ft_extract_line(char *buffer, char **temp_str,
					char **temp_buffer, int bytes_read);
char			*ft_init_and_copy_line(char **temp_str, char *buffer,
					size_t temp_size, size_t line_size);
void			ft_handle_remaining_bytes(char *buffer, char **temp_buffer,
					int bytes_read, size_t line_size);
size_t			ft_isnewline(const char *buffer, size_t bytes_read);
char			*ft_strcombine(const char *dest, const char *src);
size_t			ft_linesize(const char *buffer);
char			*ft_cut_new_line(char **all_line);
char			*ft_read_buffer(char **temp_buffer,
					t_get_next_line_var	*vars, int fd);
#endif
