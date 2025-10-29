#include "minishell.h"

void	exectscript(t_data *data)
{
	data->is_interactive = 0;
	printf("Script\n");
}

void	exect_noninteractive(t_data *data)
{
	data->is_interactive = 0;
	printf("Oneline\n");
}

void	non_interactive(t_data *data, int argc, char **argv)
{
	if (argc == 2 && argv[1] == "-c")
	{
		exectnointeractive(data);
	}
	if (argc == 2 && argv[1] == "minishell")
	{
		exectscript(data);
	}
}
