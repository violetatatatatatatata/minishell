/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_children.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:18:31 by avelandr          #+#    #+#             */
/*   Updated: 2025/12/19 16:29:35 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	prepare_fd_in(t_values *vals)
{
	int	tmp_in;

	vals->exit_val = 0;
	tmp_in = ft_open_infile(vals->token, &vals->exit_val, vals->val_env);
	if (vals->fd_prev == -1)
		vals->fd_in = tmp_in;
	else
	{
		if (tmp_in != STDIN_FILENO)
			vals->fd_in = tmp_in;
		else
			vals->fd_in = vals->fd_prev;
	}
}

static void	setup_child_output(t_values *vals)
{
	int	fd_out;

	fd_out = STDOUT_FILENO;
	if (vals->exit_val == EXIT_SUCCESS)
		fd_out = ft_open_outfile(vals->token, &vals->exit_val);
	if (fd_out > 2)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else
		dup2(vals->pipes[vals->index][1], STDOUT_FILENO);
	close(vals->pipes[vals->index][0]);
	close(vals->pipes[vals->index][1]);
}

void	ft_child_body(t_values *vals)
{
	int	return_val;

	free(vals->pids);
	vals->pids = NULL;
	ft_close_pipes(vals);
	if (vals->fd_in != STDIN_FILENO)
		dup2(vals->fd_in, STDIN_FILENO);
	setup_child_output(vals);
	if (vals->fd_in > 2)
		close(vals->fd_in);
	if (vals->exit_val != EXIT_SUCCESS)
		ft_free_vals(vals, vals->exit_val, TRUE);
	return_val = ft_exec_args(vals, vals->val_env);
	ft_free_vals(vals, return_val, TRUE);
}

void	exec_last_child(t_values *vals)
{
	int	fd_out;
	int	return_val;

	free(vals->pids);
	vals->pids = NULL;
	ft_close_pipes(vals);
	dup2(vals->fd_in, STDIN_FILENO);
	if (vals->fd_in > 0)
		close(vals->fd_in);
	if (vals->fd_prev > 2 && vals->fd_prev != vals->fd_in)
		close(vals->fd_prev);
	fd_out = STDOUT_FILENO;
	if (vals->exit_val == EXIT_SUCCESS)
		fd_out = ft_open_outfile(vals->token, &vals->exit_val);
	if (fd_out > 2)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (vals->exit_val != EXIT_SUCCESS)
		ft_free_vals(vals, vals->exit_val, TRUE);
	return_val = ft_exec_args(vals, vals->val_env);
	ft_free_vals(vals, return_val, TRUE);
}

void	ft_command_loop(t_values *vals)
{
	prepare_fd_in(vals);
	vals->pids[vals->index] = fork();
	if (vals->pids[vals->index] == -1)
	{
		perror("fork");
		free(vals->pids);
		return ;
	}
	if (vals->pids[vals->index] == 0)
		ft_child_body(vals);
	else
	{
		close(vals->pipes[vals->index][1]);
		if (vals->fd_prev != vals->fd_in && vals->fd_prev > 2)
			close(vals->fd_prev);
		vals->fd_prev = vals->pipes[vals->index][0];
	}
}
