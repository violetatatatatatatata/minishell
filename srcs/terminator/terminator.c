#include <minishell.h>

void	terminator(t_shell *data)
{
	if (g_status == 1)
		exit_shell();

}

void	exit_shell(t_shell *data)
{
	free(user_input);
	while (data->env)
	{
		free_node(data->env)
		env = env->>next;
	}
}
