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

#include <minishell.h>

int	minishell(int argc, char **argv, char **env)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	ft_memset(shell, 0, sizeof(shell));
	print_prompt();
	shell->pid = getpid();
	if (env)
		data->env = init_env(env);
	else
		handle_missing_env(data, argv[0]);
	loop(&shell);
	return (EXIT_SUCCESS);
}

