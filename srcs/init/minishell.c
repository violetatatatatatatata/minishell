/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 minishell.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelona.co	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/11/23 04:08:32 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/11/23 04:08:32 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	minishell(int argc, char **argv, char **env)
{
	t_shell	*shell;

	if (argc != 1 || argv[1] != NULL)
		return (EXIT_FAILURE);
	shell = NULL;
	shell = malloc(sizeof(t_shell));
	print_prompt();
	shell->pid = getpid();
	if (env)
		shell->env = init_env(env);
	else
		handle_missing_env(shell, argv[0]);
	loop(shell);
	terminator(shell, TRUE);
	return (EXIT_SUCCESS);
}
