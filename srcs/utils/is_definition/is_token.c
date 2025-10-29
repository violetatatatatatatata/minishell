#include "../Includes/minishell.h"

int	is_token(const char *str)
{
	if (is_word(s) || is_controlop(s) || is_redop(s))
		return (1);
	return (0);
}
