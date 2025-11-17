#include <minishell.h>

int	main(int argc, char **argv, char **env)
{
	if (!init_shell(argc, argv, env))
		return (EXIT_FAILURE);
	loop();
    terminator();
	return (EXIT_SUCCESS);
}
