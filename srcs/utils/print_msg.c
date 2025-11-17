#include <minishell.h>

int	print_msg(char *function, char *msg, int exit)
{
	printf("minishell: ");
	if (function)
		printf("%s: ", function);
	printf("%s\n", msg);
	return(exit);
}
