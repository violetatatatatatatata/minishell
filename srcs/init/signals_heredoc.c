/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 signals_heredoc.c      							:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/11/23 01:12:51 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/11/23 01:13:02 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <minishell.h>

void	set_heresign_int(int sign)
{
	printf("\n");
	g_status = sign;
}

void	signals_heredoc(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = set_heresign_int;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}
