/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 signals_heredoc.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/11/26 12:21:11 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/11/26 12:21:11 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <minishell.h>

// cuando se interrumpe con sigint el exit es 130
void	sig_heredoc_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	exit(130);
}

// se ejecuta en un fork porque haciendo ctrl c matarias al padre
void	set_signals_heredoc(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
	act.sa_handler = &sig_heredoc_handler;
	sigaction(SIGINT, &act, NULL);
}
