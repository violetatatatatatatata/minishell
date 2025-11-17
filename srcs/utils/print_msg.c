#include <minishell.h>

void	print_msg(char *msg, int* exit)
{
	printf("%s%s%s\n", exit, msg, RESET);
}
