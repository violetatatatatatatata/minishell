/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exect_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 19:48:43 by avelandr          #+#    #+#             */
/*   Updated: 2025/12/17 19:49:25 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_manage_redirects(t_values *vals, int fd_out)
{
	if (vals->fd_in != STDIN_FILENO)
	{
		if (dup2(vals->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			ft_free_vals(vals, EXIT_FAILURE, TRUE);
		}
		close(vals->fd_in);
	}
	if (fd_out > 2)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else if (vals->index < vals->cmds_size - 1)
		dup2(vals->pipes[vals->index][1], STDOUT_FILENO);
}

void	ft_child_body(t_values *vals)
{
	int	fd_out;

	free(vals->pids);
	vals->pids = NULL;
	fd_out = STDOUT_FILENO;
	if (vals->exit_val == EXIT_SUCCESS)
		fd_out = ft_open_outfile(vals->token, &vals->exit_val);
	ft_manage_redirects(vals, fd_out);
	ft_close_pipes(vals);
	if (vals->exit_val != EXIT_SUCCESS)
		ft_free_vals(vals, vals->exit_val, TRUE);
	ft_free_vals(vals, ft_exec_args(vals, vals->val_env), TRUE);
}

static void	ft_prepare_input(t_values *vals)
{
	int	tmp_in;

	vals->exit_val = 0;
	tmp_in = ft_open_infile(vals->token, &vals->exit_val);
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

void	ft_last_cmd(t_values *vals)
{
	ft_prepare_input(vals);
	vals->pids[vals->index] = fork();
	if (vals->pids[vals->index] == -1)
		return (perror("fork"), free(vals->pids));
	if (vals->pids[vals->index] == 0)
		ft_child_body(vals);
}

void	ft_command_loop(t_values *vals)
{
	ft_prepare_input(vals);
	vals->pids[vals->index] = fork();
	if (vals->pids[vals->index] == -1)
		return (perror("fork"), free(vals->pids));
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
