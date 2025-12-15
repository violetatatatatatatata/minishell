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
	t_shell	shell;

	(void)argc;
	(void)argv;
	print_prompt();
	shell.pid = getpid();
	shell.exit_status = 0;
	if (env)
		shell.env = init_env(env);
	else
		handle_missing_env(&shell, argv[0]);
	loop(&shell);
	terminator(&shell, shell.exit_status, TRUE);
	return (EXIT_SUCCESS);
}
