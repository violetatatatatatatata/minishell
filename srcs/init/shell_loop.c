static void	clean_loop_data(t_shell *data)
{
	if (data->user_input)
	{
		free(data->user_input);
		data->user_input = NULL;
	}
// puedo hacer que dependiendo del valor de la variable global, libere TODOS
// los recursos o tan solo los que han sido usados para el ultimo comando ejecutado
	terminator(); 
}

void	loop()
{
	char	*prompt_str;

	while (1)
	{
		set_signals_interactive();
		prompt_str = prompt();
		data->user_input = readline(prompt_str);
		free(prompt_str);
		if (data->user_input == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			terminator(data);
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
		clean_loop_data(data);
	}
}

