/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_triple(char ***arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		ft_free_double(arr[i++]);
	free(arr);
	arr = NULL;
}

void	ft_free_double(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_cmd(void *content)
{
	t_cmd_table	*table;

	table = (t_cmd_table *)content;
	if (table)
		ft_free_cmd_list(table);
}

void	ft_free_vals(t_values *vals, int exit_status, int is_exit)
{
	if (vals->pids)
		free(vals->pids);
	vals->pids = NULL;
	if (vals->pipes)
		ft_free_pipes(vals, vals->cmds_size - 1);
	if (vals->cmd_list)
		ft_lstclear(&vals->cmd_list, &free_cmd);
	vals->cmd_list = NULL;
	terminator(vals->val_env, exit_status, is_exit);
	vals->val_env = NULL;
}
