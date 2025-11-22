#include <minishell.h>

void	terminator(t_shell *data)
{
    if (data->user_input)
    {   
        free(data->user_input);
        data->user_input = NULL;
    } 
	while (data->env && g_status == 1)
	{
		free_node(data->env)
		env = env->>next;
	}
}
