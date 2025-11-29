/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/11/28 12:47:05 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	debug_fd(int fd) //ELIMINAR PARA LA ENTREGA FINAL
{
	char	buffer[1024];
	ssize_t	n;

	if (fd < 0)
	{
		printf("fd inválido\n");
		return ;
	}
	lseek(fd, 0, SEEK_SET);
	n = read(fd, buffer, sizeof(buffer) - 1);
	while (n > 0)
	{
		buffer[n] = '\0';
		printf("%s", buffer);
		n = read(fd, buffer, sizeof(buffer) - 1);
	}
	printf("\n");
}

static void	ft_child_body(t_values *vals, int *fd_pipe)
{
	int	fd_out;
	int	return_val;

	free(vals->pids);
	vals->pids = NULL;
	if (vals->fd_in != STDIN_FILENO)
		dup2(vals->fd_in, STDIN_FILENO);
	fd_out = ft_open_outfile(vals->token);
	if (fd_out > 2)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else
		dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	if (vals->fd_in > 2)
		close(vals->fd_in);
	return_val = ft_exec_args(vals, vals->val_env);
	ft_free_vals(vals);
	exit(return_val);
}

static void	ft_last_cmd(t_values *vals)
{
	int	fd_out;
	int	return_val;
	int	tmp_in;

	tmp_in = ft_open_infile(vals->token);
	if (vals->fd_prev == -1)
		vals->fd_in = tmp_in;
	else
	{
		if (tmp_in != STDIN_FILENO)
			vals->fd_in = tmp_in;
		else
			vals->fd_in = vals->fd_prev;
	}
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
		if (vals->fd_prev > 2 && vals->fd_prev != vals->fd_in)
			close(vals->fd_prev);
		fd_out = ft_open_outfile(vals->token);
		if (fd_out > 2)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		return_val = ft_exec_args(vals, vals->val_env);
		ft_free_vals(vals);
		exit(return_val);
	}
}

static void	ft_command_loop(t_values *vals, int fd_pipe[2])
{
	int	tmp_in;

	tmp_in = ft_open_infile(vals->token);
	printf("FORK: %i\n", vals->index);
	if (pipe(fd_pipe) == -1)
		return (perror("Pipe"), free(vals->pids), exit(EXIT_FAILURE));
	vals->fd_in = ft_open_infile(vals->token);
	if (vals->fd_prev == -1)
		vals->fd_in = tmp_in;
	else
	{
		if (tmp_in != STDIN_FILENO)
			vals->fd_in = tmp_in;
		else
			vals->fd_in = vals->fd_prev;
	}
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

int	ft_exec_cmd_line(t_list *cmd_list, t_shell *data)
{
	int			fd_pipe[2];
	int			ret_val;
	t_values	vals;
	t_cmd_table	*table;

	vals.val_env = data;
	vals.fd_prev = -1;
	vals.index = 0;
	vals.cmds_size = ft_lstsize(cmd_list);
	vals.cmd_list = cmd_list;
	printf("CMDS SIZE: %i\n", vals.cmds_size);
	table = (t_cmd_table *)cmd_list->content;
	if (vals.cmds_size == 1 && ft_is_buitlin(table->token->content))
	{
		printf("SOLO BUILT-IN\n");
		vals.token = table->token;
		vals.args = table->args;
		return (ft_exec_builtin(&vals, data));
	}
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
	return (ret_val);
}
