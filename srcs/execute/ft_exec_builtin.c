/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/11/28 13:03:05 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_exec_builtin(t_values *data, t_shell *shell)
{
	char	*str;
	int		val_ret;

	val_ret = EXIT_SUCCESS;
	str = data->args[0];
	if (!ft_strncmp(str, "cd", sizeof("cd")))
		val_ret = bt_cd(data->args, data);
	else if (!ft_strncmp(str, "echo", sizeof("echo")))
		bt_echo(data->args);
	else if (!ft_strncmp(str, "env", sizeof("env")))
		val_ret = bt_env(shell, data->args);
	else if (!ft_strncmp(str, "exit", sizeof("exit")))
		val_ret = bt_exit(shell, data->args, data->cmd_list);
	else if (!ft_strncmp(str, "export", sizeof("export")))
		val_ret = bt_export(shell, data->args);
	else if (!ft_strncmp(str, "pwd", sizeof("pwd")))
		bt_pwd(shell);
	else if (!ft_strncmp(str, "unset", sizeof("unset")))
		val_ret = bt_unset(shell, data->args);
	return (val_ret);
}
