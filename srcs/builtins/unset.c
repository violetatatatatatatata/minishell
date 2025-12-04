/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:59:13 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/25 15:39:56 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_envremove(t_shell *data, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = data->env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				data->env = current->next;
			free_node(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	bt_unset(t_shell *data, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_envremove(data, args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
