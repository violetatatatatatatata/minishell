#include <minishell.h>

int main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)env;
	ft_memset(&data, 0, sizeof(t_data));
	if (!check_execution(&data, argc, argv))
	{
		print_msg(INPUT_ERROR, RED);
		return(EXIT_FAILURE);
	}
	//	exit_shelly();
	if (data.is_interactive)
		exect_interactive(&data);
	else
		exect_noninteractive(&data, argc, argv);//temporal
//	exit_shelly(&data);
	return (EXIT_SUCCESS);
}
