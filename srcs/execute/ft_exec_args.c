/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/12/17 18:25:26 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_path_error_message(char **argv)
{
	if (!argv || !argv[0])
		ft_putstr_fd("pipex: command not found\n", 2);
	else
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

static int	ft_prepare_exec(char **args, t_shell *data, char **cmd_path)
{
	if (!args)
	{
		ft_path_error_message(args);
		return (127);
	}
	*cmd_path = ft_find_command_path(args[0], data);
	if (!*cmd_path)
	{
		ft_path_error_message(args);
		return (127);
	}
	return (EXIT_SUCCESS);
}

int	ft_exec_args(t_values *vals, t_shell *data)
{
	char	*cmd_path;
	int		return_val;
	char	**env;

	if (ft_is_buitlin(vals->args[0]))
	{
		return (ft_exec_builtin(vals, data));
	}
	return_val = ft_prepare_exec(vals->args, data, &cmd_path);
	if (return_val > EXIT_SUCCESS)
		return (return_val);
	env = env_to_array(data->env);
	execve(cmd_path, vals->args, env);
	if (env)
		ft_free_split(env);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(vals->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free(cmd_path);
	return (127);
}
