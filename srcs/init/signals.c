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

void	reset_prompt(int signo)
{
	// g_status = 130 (128 + 2) deberia ser relevante para las expansiones de $?
	(void)signo;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("");
	rl_display();
}

/*
** Configura los handlers de señal para la fase INTERACTIVA
   (mientras se espera input, antes de rl).
** - SIGQUIT (Ctrl-\): ignorar.
** - SIGINT (Ctrl-C): llama a reset_prompt
*/
void	set_signals_interactive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
	act.sa_handler = &reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

/*
** Configura los handlers de señal para la fase de EJECUCIÓN
   (después de readline).
** - SIGINT y SIGQUIT: Llama a signal_print_newline
** signal_print_newline maneja la interrupcion durante la ejecucion
*/
void	set_signals_handlers_exec(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
