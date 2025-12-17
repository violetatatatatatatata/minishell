/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/12/17 18:00:24 by avelandr         ###   ########.fr       */
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

// se ha modificado porque al hacer ls | sdjkhk | date
// ignoraba el comando incorrecto de la mitad
static void	ft_child_body(t_values *vals)
{
	int	fd_out;
	int	return_val;

	free(vals->pids);
	vals->pids = NULL;
	// antes de cerrar las pipes se ha de configurar la entrada
	if (vals->fd_in != STDIN_FILENO)
	{
		// ademas se han de controlar errores
		if (dup2(vals->fd_in, STDIN_FILENO) == -1)
		{
			perror("");
			ft_free_vals(vals, EXIT_FAILURE, TRUE);
		}
		close(vals->fd_in); // cerrar el original ya duplicado
	}
	fd_out = STDOUT_FILENO;
	if (vals->exit_val == EXIT_SUCCESS)
		fd_out = ft_open_outfile(vals->token, &vals->exit_val);
	if (fd_out > 2)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else if (vals->index < vals->cmds_size - 1) // si NO es el último comando
		dup2(vals->pipes[vals->index][1], STDOUT_FILENO);
	// aqui si se cierran las pipes
	ft_close_pipes(vals);
	if (vals->exit_val != EXIT_SUCCESS)
		ft_free_vals(vals, vals->exit_val, TRUE);
	return_val = ft_exec_args(vals, vals->val_env);
	ft_free_vals(vals, return_val, TRUE);
}

/*
static void	ft_child_body(t_values *vals)
{
	int	fd_out;
	int	return_val;

	free(vals->pids);
	vals->pids = NULL;
	ft_close_pipes(vals);
	if (vals->fd_in != STDIN_FILENO)
		dup2(vals->fd_in, STDIN_FILENO);
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
	if (vals->fd_in > 2)
		close(vals->fd_in);
	if (vals->exit_val != EXIT_SUCCESS)
		ft_free_vals(vals, vals->exit_val, TRUE);
	return_val = ft_exec_args(vals, vals->val_env);
	ft_free_vals(vals, return_val, TRUE);
}
*/
static void	ft_last_cmd(t_values *vals)
{
	int	fd_out;
	int	return_val;
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
	vals->pids[vals->index] = fork();
	if (vals->pids[vals->index] == -1)
		return (perror("Couldn't create child"),
			free(vals->pids));
	if (vals->pids[vals->index] == 0)
	{
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
		if (vals->exit_val == EXIT_SUCCESS)
			ft_free_vals(vals, return_val, TRUE);
		ft_free_vals(vals, vals->exit_val, TRUE);
	}
}

static void	ft_command_loop(t_values *vals)
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
	vals->pids[vals->index] = fork();
	if (vals->pids[vals->index] == -1)
		return (perror("Couldn't create child"),
			free(vals->pids));
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

int	ft_exec_cmd_line(t_list *cmd_list, t_shell *data)
{
	int			ret_val;
	t_values	vals;
	t_cmd_table	*table;

	vals.val_env = data;
	vals.fd_prev = -1;
	vals.index = 0;
	vals.cmds_size = ft_lstsize(cmd_list);
	vals.cmd_list = cmd_list;
	table = (t_cmd_table *)cmd_list->content;
	if (ft_set_pipes(&vals) != 0)
		return (EXIT_FAILURE);
	//ft_set_pipes(&vals);
	if (vals.cmds_size == 1 && ft_is_buitlin(table->token->content))
	{
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
		ft_command_loop(&vals);
		vals.index++;
		cmd_list = cmd_list->next;
	}
	if (vals.fd_in > 2)
		close(vals.fd_in);
	if (vals.fd_prev > 2 && vals.fd_prev != vals.fd_in)
		close(vals.fd_prev);
	ft_free_pipes(&vals, vals.cmds_size - 1);
	ret_val = ft_wait_children(vals.cmds_size, vals.pids);
	return (ret_val);
}
