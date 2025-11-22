#include <minishell.h>

void	terminator(t_shell *data, int exit)
{
    if (data->user_input)
    {   
        free(data->user_input);
        data->user_input = NULL;
    }
	// free la parte de alex
	if (exit)
	{
		if (data->env)
			ft_lstclear_env(&data->env)
		rl_clear_history();
		exit(g_status);
	}
}
