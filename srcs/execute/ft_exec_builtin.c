/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/06/02 10:55:31 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_restore(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static int	ft_redirections(t_values *data)
{
	data->fd_in = ft_open_infile(data->token);
	if (data->fd_in == -2)
		return (EXIT_FAILURE);
	data->fd_out = ft_open_outfile(data->token);
	if (data->fd_in != STDIN_FILENO && data->fd_in > 0)
	{
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
	if (data->fd_out != STDOUT_FILENO && data->fd_out > 0)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
	return (EXIT_SUCCESS);
}

static int	ft_run_builtin(t_values *data, t_shell *shell)
{
	char	*str;

	str = data->args[0];
	if (!ft_strncmp(str, "cd", sizeof("cd")))
		return (bt_cd(data->args, data));
	if (!ft_strncmp(str, "echo", sizeof("echo")))
		return (bt_echo(data->args), EXIT_SUCCESS);
	if (!ft_strncmp(str, "env", sizeof("env")))
		return (bt_env(shell, data->args));
	if (!ft_strncmp(str, "export", sizeof("export")))
		return (bt_export(shell, data->args));
	if (!ft_strncmp(str, "pwd", sizeof("pwd")))
		return (bt_pwd(shell), EXIT_SUCCESS);
	if (!ft_strncmp(str, "unset", sizeof("unset")))
		return (bt_unset(shell, data->args));
	return (EXIT_SUCCESS);
}

int	ft_exec_builtin(t_values *data, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (!ft_strncmp(data->args[0], "exit", sizeof("exit")))
	{
		ft_restore(saved_stdin, saved_stdout);
		return (bt_exit(shell, data->args, data->cmd_list));
	}
	if (ft_redirections(data) == EXIT_FAILURE)
		return (2);
	ret = ft_run_builtin(data, shell);
	ft_restore(saved_stdin, saved_stdout);
	return (ret);
}
