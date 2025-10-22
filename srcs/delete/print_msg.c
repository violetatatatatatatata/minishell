#include <minishell.h>

void	print_msg(char *msg, int COLOR)
{
	printf("%s%s%s\n", COLOR, msg, RESET);
}
