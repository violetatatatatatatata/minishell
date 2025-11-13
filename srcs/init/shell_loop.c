void	loop()
{
	if (shell->interactive)
		set_signals_interactive();
    rl_input();
    set_signals_handlers_exec();
    if (*data->user_input && data->user_input)
    {
        add_history(data->user_input);
        if (lexparsexpander(data) == TRUE)
            g_status = execute(data);
        else
            g_status = 1;
    }
}
