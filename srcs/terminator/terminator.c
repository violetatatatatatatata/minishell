/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 terminator.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/11/23 01:14:30 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/11/23 01:14:30 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <minishell.h>

void	terminator(t_shell *data, int exit_status, int is_exit)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (data->user_input)
	{
		free(data->user_input);
		data->user_input = NULL;
	}
	if (is_exit)
	{
		if (data->env)
			ft_lstclear_env(&data->env);
		rl_clear_history();
		exit(exit_status);
	}
}
