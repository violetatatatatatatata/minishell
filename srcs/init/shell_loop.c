#include <minishell.h>

// puedo hacer que dependiendo del valor de la variable global, libere TODOS
// los recursos o tan solo los que han sido usados para el ultimo comando ejecutado
void	loop()
{
	char	*prompt_str;

	while (1)
	{
		set_signals_interactive();
		prompt_str = prompt();
		data->user_input = readline(prompt_str);
		free(prompt_str);
		// cuando readline detecta ctrl-d devuelve NULL
		if (data->user_input == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			terminator(data, TRUE);
		}
		set_signals_handlers_exec();
		if (data->user_input && data->user_input[0] != '\0')
		{
			add_history(data->user_input);
			if (lexparsexpander(data) == TRUE)
				g_status = execute(data);
			else
				g_status = 1;
		}
		terminator(data, FALSE);
	}
}
