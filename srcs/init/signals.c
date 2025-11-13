#include <minishell.h>

void    reset_prompt(int signo)
{
    (void)signo;
    write (1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("");
    rl_display();
}

/*  man 7 signal
    SIGINT (2): interrupción de teclado (Ctrl-C)
    SIGQUIT (3): salida de teclado (Ctrl-\)
*/

void	signals(t_data *data)
{
    struct sigaction    act;

    ft_memset(&act, 0, sizeof(act));
    act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
    act.sa_handler = &reset_prompt;
    sigaction(SIGINT, &act, NULL);
    data->user_input = readline(prompt());
    if (data->user_input == NULL)
    {
        free_data(data, TRUE);
        return ;
    }
	act.sa_handler = &signal_print_newline;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);
    if (*data->user_input && data->user_input)
        add_history(data->user_input);
    if (parse_input(data) == TRUE)
        g_status = execute(data);
    else
        g_status = 1;
    free_data(data, FALSE);

}
