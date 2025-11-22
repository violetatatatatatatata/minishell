#include <minishell.h>

/*void	reset_prompt(int signo)
{
	// g_status = 130 (128 + 2) deberia ser relevante para las expansiones de $?
	(void)signo;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("");
	rl_display();
}*/

/*
** Configura los handlers de señal para la fase INTERACTIVA
   (mientras se espera input, antes de rl).
** - SIGQUIT (Ctrl-\): ignorar.
** - SIGINT (Ctrl-C): llama a reset_prompt
*/
/*void	set_signals_interactive()
{
    struct sigaction    act;

    ft_memset(&act, 0, sizeof(act));
    // (ctrl \)
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
    // (ctrl C)
	act.sa_handler = &reset_prompt;
    sigaction(SIGINT, &act, NULL);
}*/

/*
** Configura los handlers de señal para la fase de EJECUCIÓN
   (después de readline).
** - SIGINT y SIGQUIT: Llama a signal_print_newline
     (o la lógica para los hijos).
** signal_print_newline maneja la interrupcion durante la ejecucion
*/
/*void	set_signals_handlers_exec()
{
    struct sigaction    act;

    ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);
}*/

/*void	signals(t_data *data)
{
	data->user_input = readline(prompt());
    if (data->user_input == NULL)
    {
		print_msg(NULL, "empty input", EXIT_FAILURE);
        terminator(data);
    }
	if (*data->user_input && data->user_input)
        add_history(data->user_input);
    if (parse_input(data) == TRUE)
        g_status = execute(data);
    else
        g_status = 1;
}*/
