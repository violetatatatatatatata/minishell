/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:09:25 by avelandr          #+#    #+#             */
/*   Updated: 2025/12/21 19:10:37 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_prepare_exec(char **args, t_shell *data, char **cmd_path)
{
	struct stat	st;

	*cmd_path = ft_find_command_path(args[0], data);
	if (!*cmd_path)
		return (print_msg(*cmd_path, NOT_CMD_MSG, 127));
	else if (stat(*cmd_path, &st) != 0)
		return (print_msg(*cmd_path, NOT_CMD_MSG, 127));
	else if (S_ISDIR(st.st_mode))
		return (print_msg(*cmd_path, IS_DIRECORY, 126));
	else if (access(*cmd_path, X_OK) != 0)
		return (print_msg(*cmd_path, NOT_PERMISSION_MSG, 126));
	return (EXIT_SUCCESS);
}

int	ft_exec_args(t_values *vals, t_shell *data)
{
	char	*cmd_path;
	int		return_val;
	char	**env;

	if (!vals->args)
		return (0);
	if (ft_is_buitlin(vals->args[0]))
		return (ft_exec_builtin(vals, data));
	return_val = ft_prepare_exec(vals->args, data, &cmd_path);
	if (return_val > EXIT_SUCCESS)
	{
		if (cmd_path)
			free(cmd_path);
		return (return_val);
	}
	env = env_to_array(data->env);
	execve(cmd_path, vals->args, env);
	ft_free_split(env);
	print_msg(cmd_path, NOT_CMD_MSG, 2);
	free(cmd_path);
	return (127);
}
