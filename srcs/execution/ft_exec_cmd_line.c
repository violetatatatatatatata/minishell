/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/08/07 13:23:03 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_child_body(t_values *vals,
	int *fd_pipe, char ***args)
{
	int	fd_out;
	int	return_val;

	free(vals->pids);
	vals->pids = NULL;
	close(fd_pipe[0]);
	dup2(vals->fd_in, STDIN_FILENO);
	if (vals->fd_prev != vals->fd_in)
		close(vals->fd_prev);
	fd_out = ft_open_outfile(args);
	if (fd_out == 0)
		dup2(fd_pipe[1], STDOUT_FILENO);
	else
		dup2(fd_out, STDOUT_FILENO);
	close(fd_pipe[1]);
	if (fd_out > 0)
		close(fd_out);
	return_val = ft_exec_args(*args, vals->env);
	ft_free_vals(vals);
	exit(return_val);
}

static void	ft_last_cmd(t_values *vals, int i, char ***args)
{
	int	fd_out;
	int	return_val;

	vals->fd_in = ft_open_infile(args);
	if (vals->fd_prev == -1)
		vals->fd_prev = vals->fd_in;
	printf("Last cmd fd_in: %i\n", vals->fd_in);
	vals->pids[i] = fork();
	if (vals->pids[i] == -1)
		return (perror("Couldn't create child"),
			free(vals->pids), exit(EXIT_FAILURE));
	if (vals->pids[i] == 0)
	{
		free(vals->pids);
		vals->pids = NULL;
		dup2(vals->fd_in, STDIN_FILENO);
		if (vals->fd_in > 0)
			close(vals->fd_in);
		if (vals->fd_prev >= 0 && vals->fd_prev != vals->fd_in)
			close(vals->fd_prev);
		fd_out = ft_open_outfile(args);
		if (fd_out > 2)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		return_val = ft_exec_args(*args, vals->env);
		ft_free_vals(vals);
		exit(return_val);
	}
}

static void	ft_command_loop(t_values *vals, int fd_pipe[2], char ****cmd_list)
{
	int	i;

	vals->fd_prev = -1;
	i = 0;
	while (i < vals->num_cmds - 1)
	{
		printf("FORK: %i\n", i);
		if (pipe(fd_pipe) == -1)
			return (perror("Pipe"), free(vals->pids), exit(EXIT_FAILURE));
		vals->fd_in = ft_open_infile(&(*cmd_list)[i]);
		if (vals->fd_prev == -1)
			vals->fd_prev = vals->fd_in;
		vals->pids[i] = fork();
		if (vals->pids[i] == -1)
			return (perror("Couldn't create child"),
				free(vals->pids), exit(EXIT_FAILURE));
		if (vals->pids[i] == 0)
		{
			ft_child_body(vals, fd_pipe, &(*cmd_list)[i]);
		}
		else
		{
			close(fd_pipe[1]);
			if (vals->fd_prev != vals->fd_in && vals->fd_prev > 2)
				close(vals->fd_prev);
			vals->fd_prev = fd_pipe[0];
			i++;
		}
	}
	ft_last_cmd(vals, i, &(*cmd_list)[i]);
}

void	ft_exec_cmd_line(t_values *vals)
{
	int		fd_pipe[2];

	vals->tokens_list = ft_command_list(vals);
	ft_command_loop(vals, fd_pipe, &vals->tokens_list);
	if (vals->fd_in > 2)
		close(vals->fd_in);
	if (vals->fd_prev > 2 && vals->fd_prev != vals->fd_in)
		close(vals->fd_prev);
}
