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

#include "../includes/minishell.h"

void debug_fd(int fd)
{
    if (fd < 0) {
        printf("fd inválido\n");
        return;
    }

    // Obtener tamaño aproximado
    char buffer[1024];
    ssize_t n;

    // Mover cursor al inicio (solo si es un file normal)
    lseek(fd, 0, SEEK_SET);

    while ((n = read(fd, buffer, sizeof(buffer)-1)) > 0)
    {
        buffer[n] = '\0';  // Terminar string
        printf("%s", buffer);
    }

    printf("\n");
}

static void	ft_child_body(t_values *vals,
	int *fd_pipe)
{
	int	fd_out;
	int	return_val;

	free(vals->pids);
	vals->pids = NULL;
	close(fd_pipe[0]);
	dup2(vals->fd_in, STDIN_FILENO);
	if (vals->fd_prev != vals->fd_in)
		close(vals->fd_prev);
	fd_out = ft_open_outfile(vals->token);
	if (fd_out == 1)
		dup2(fd_pipe[1], STDOUT_FILENO);
	else
		dup2(fd_out, STDOUT_FILENO);
	close(fd_pipe[1]);
	if (fd_out > 0)
		close(fd_out);
	return_val = ft_exec_args(vals->args, vals->env);
	ft_free_vals(vals);
	exit(return_val);
}

static void	ft_last_cmd(t_values *vals)
{
	int	fd_out;
	int	return_val;

	vals->fd_in = ft_open_infile(vals->token);
	if (vals->fd_prev == -1)
		vals->fd_prev = vals->fd_in;
	printf("LAST FORK: %i\n", vals->index);
	printf("Last cmd fd_in: %i\n", vals->fd_in);
	vals->pids[vals->index] = fork();
	if (vals->pids[vals->index] == -1)
		return (perror("Couldn't create child"),
			free(vals->pids), exit(EXIT_FAILURE));
	if (vals->pids[vals->index] == 0)
	{
		free(vals->pids);
		vals->pids = NULL;
		dup2(vals->fd_in, STDIN_FILENO);
		if (vals->fd_in > 0)
			close(vals->fd_in);
		if (vals->fd_prev >= 0 && vals->fd_prev != vals->fd_in)
			close(vals->fd_prev);
		fd_out = ft_open_outfile(vals->token);
		if (fd_out > 2)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		return_val = ft_exec_args(vals->args, vals->env);
		ft_free_vals(vals);
		exit(return_val);
	}
}

static void	ft_command_loop(t_values *vals, int fd_pipe[2])
{
	printf("FORK: %i\n", vals->index);
	if (pipe(fd_pipe) == -1)
		return (perror("Pipe"), free(vals->pids), exit(EXIT_FAILURE));
	vals->fd_in = ft_open_infile(vals->token);
	if (vals->fd_prev == -1)
		vals->fd_prev = vals->fd_in;
	vals->pids[vals->index] = fork();
	if (vals->pids[vals->index] == -1)
		return (perror("Couldn't create child"),
			free(vals->pids), exit(EXIT_FAILURE));
	if (vals->pids[vals->index] == 0)
		ft_child_body(vals, fd_pipe);
	else
	{
		close(fd_pipe[1]);
		if (vals->fd_prev != vals->fd_in && vals->fd_prev > 2)
			close(vals->fd_prev);
		vals->fd_prev = fd_pipe[0];
	}
}

void	ft_exec_cmd_line(t_list *cmd_list, char **env)
{
	int			fd_pipe[2];
	int			ret_val;
	t_values	vals;
	t_cmd_table	*table;

	vals.env = env;
	vals.fd_prev = -1;
	vals.index = 0;
	vals.cmds_size = ft_lstsize(cmd_list);
	printf("CMDS SIZE: %i\n", vals.cmds_size);
	vals.pids = malloc(sizeof(pid_t) * vals.cmds_size);
	while (cmd_list)
	{
		table = (t_cmd_table *)cmd_list->content;
		vals.token = table->token;
		vals.args = table->args;
		if (!cmd_list->next)
		{
			ft_last_cmd(&vals);
			break ;
		}
		ft_command_loop(&vals, fd_pipe);
		vals.index++;
		cmd_list = cmd_list->next;
	}
	ret_val = ft_wait_children(vals.cmds_size, vals.pids);
	if (vals.fd_in > 2)
		close(vals.fd_in);
	if (vals.fd_prev > 2 && vals.fd_prev != vals.fd_in)
		close(vals.fd_prev);
}
