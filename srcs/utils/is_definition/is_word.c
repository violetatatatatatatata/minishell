#include <minishell.h>

int	is_word(const char *s)
{
	while (*s)
	{
		if (*s != ' ' || *s != '\t' || !ft_ismeta(*s))
			return (0);
		s++;
	}
	return (1);
}
