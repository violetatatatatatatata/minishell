#include <minishell.h>

int	is_controlop(const char *s)
{
	if (ft_strcmp((char *)s, "||") == 0 || ft_strcmp((char *)s, "&&") == 0
		|| ft_strcmp((char *)s, "&") == 0 || ft_strcmp((char *)s, ";") == 0
		|| ft_strcmp((char *)s, ";;") == 0 || ft_strcmp((char *)s, "(") == 0
		|| ft_strcmp((char *)s, ")") == 0 || ft_strcmp((char *)s, "|") == 0
		|| ft_strcmp((char *)s, "!") == 0)
		return (1);
	return (0);
}
