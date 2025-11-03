#include <minishell.h>

int main(int argc, char **argv, char **env)
{
	// t_data	data;

	(void)env;
	// ft_memset(&data, 0, sizeof(t_data));
	if (!init_shell(argc, argv, env))
	{
		print_msg(INPUT_ERROR, RED);
		return(EXIT_FAILURE);
	}
	shell_loop();
	terminator();
return (EXIT_SUCCESS);
}

/*
	if (data.is_interactive)
		exect_interactive(&data);
	else
		exect_noninteractive(&data, argc, argv);//temporal
*/
