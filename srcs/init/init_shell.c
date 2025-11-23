/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 01:10:58 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/23 03:11:13 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_shell(int argc, char **argv, char **env)
{
	t_shell	data;

	ft_memset(&data, 0, sizeof(data));
	print_prompt();
	shell->pid = getpid();
	if (env)
		data->env = init_env(env);
	else
		handle_missing_env(data, argv[0]);
}

/*
int	args_checker(int argc, char **argv)
{
	if (argc != 1 && argc != 3)
		return (print_msg(NULL, "args error", EXIT_FAILURE));
	if (argc == 3)
	{
		data->interactive = FALSE;
		if (!argv[1] || (argv[1] && ft_strcmp(argv[1], "-c") != 0))
			return (print_msg(NULL, "args error", EXIT_FAILURE));
		else if (!argv[2] || (argv[2] && argv[2][0] == '\0'))
			return (print_msg(NULL, "args error", EXIT_FAILURE));
	}
	else
		data->interactive = TRUE;
	return (EXIT_SUCCESS);
}
*/
