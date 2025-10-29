#include "../Includes/minishell.h"

int	is_word(const char *s)
{
	while (*s)
	{
		if (*s != ' ' || *s != '\t' || !is_meta(s))
			return (0);
		s++;
	}
	return (1);
}
