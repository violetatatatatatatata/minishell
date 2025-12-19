/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:10:50 by avelandr          #+#    #+#             */
/*   Updated: 2025/12/19 16:35:15 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_init_exec_vars(t_values *vals, t_shell *data, t_list *cmd_list)
{
	vals->val_env = data;
	vals->fd_prev = -1;
	vals->index = 0;
	vals->cmds_size = ft_lstsize(cmd_list);
	vals->cmd_list = cmd_list;
}

static int	ft_handle_single_builtin(t_values *vals, t_shell *data)
{
	t_cmd_table	*table;

	table = (t_cmd_table *)vals->cmd_list->content;
	if (vals->cmds_size == 1 && ft_is_buitlin(table->token->content))
	{
		vals->token = table->token;
		vals->args = table->args;
		return (ft_exec_builtin(vals, data));
	}
	return (-1);
}

static int	ft_finish_execution(t_values *vals)
{
	int	ret_val;

	if (vals->fd_in > 2)
		close(vals->fd_in);
	if (vals->fd_prev > 2 && vals->fd_prev != vals->fd_in)
		close(vals->fd_prev);
	ft_free_pipes(vals, vals->cmds_size - 1);
	ret_val = ft_wait_children(vals->cmds_size, vals->pids);
	free(vals->pids);
	return (ret_val);
}

void	ft_loop_pipeline(t_values *vals)
{
	t_cmd_table	*table;

	while (vals->cmd_list)
	{
		table = (t_cmd_table *)vals->cmd_list->content;
		vals->token = table->token;
		vals->args = table->args;
		if (!vals->cmd_list->next)
		{
			ft_last_cmd(vals);
			break ;
		}
		ft_command_loop(vals);
		vals->index++;
		vals->cmd_list = vals->cmd_list->next;
	}
}

int	ft_exec_cmd_line(t_list *cmd_list, t_shell *data)
{
	t_values	vals;
	int			builtin_ret;

	ft_init_exec_vars(&vals, data, cmd_list);
	if (ft_set_pipes(&vals) != 0)
		return (EXIT_FAILURE);
	builtin_ret = ft_handle_single_builtin(&vals, data);
	if (builtin_ret != -1)
		return (builtin_ret);
	vals.pids = malloc(sizeof(pid_t) * vals.cmds_size);
	if (!vals.pids)
	{
		ft_free_pipes(&vals, vals.cmds_size - 1);
		return (perror("malloc"), EXIT_FAILURE);
	}
	ft_loop_pipeline(&vals);
	return (ft_finish_execution(&vals));
}
