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

	if (!arr ||!*arr)
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

/*void	ft_free_cmd_list(char ***list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (list[i])
	{
		while (list[i][j])
		{
			free(list[i][j]);
			j++;
		}
		free(list[i]);
		i++;
	}
	free(list);
}*/

void	free_cmd(void *content)
{
	t_cmd_table	*node;

	node = (t_cmd_table *)content;
	if (!node)
		return ;
	if (node->args)
		ft_free_split(node->args);
	ft_free_cmd_list(node);
}

void	ft_free_vals(t_values *vals, int exit_status, int is_exit)
{
	if (vals->pids)
		free(vals->pids);
	if (vals->pipes)
		ft_free_pipes(vals, vals->cmds_size - 1);
	if (vals->cmd_list)
		ft_lstclear(&vals->cmd_list, &free_cmd);
	vals->cmd_list = NULL;
	terminator(vals->val_env, exit_status, is_exit);
}
