/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 signals.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/11/23 01:12:51 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/11/23 01:13:02 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <minishell.h>

// g_status = 130 (128 + 2) deberia ser relevante para las expansiones de $?
void	reset_prompt(int signo)
{
	(void)signo;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_heredoc_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	exit(130);
}

void	set_signals(void (*handler)(int))
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	if (handler == SIG_DFL)
		act.sa_handler = SIG_DFL;
	else
		act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
	act.sa_handler = handler;
	sigaction(SIGINT, &act, NULL);
}

void	set_signals_handlers_exec(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
