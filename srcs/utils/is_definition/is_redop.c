#include "../Includes/minishell.h"

int	is_redop(const char *str)
{
	if (ft_strcmp(s, ">") == 0 || ft_strcmp(s, ">>") == 0
		|| ft_strcmp(s, "<") == 0 || ft_strcmp(s, "<<") == 0
		|| ft_strcmp(s, "<>") == 0 || ft_strcmp(s, "&>") == 0
		|| ft_strcmp(s, "2>&1") == 0)
		return (1);
	return (0);
}
