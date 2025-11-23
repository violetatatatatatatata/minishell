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

#include "minishell.h"

void	ft_free_tokens(char **tokens)
{
	int	i;

	if (!tokens ||!*tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	free(tokens);
	tokens = NULL;
}

void	ft_free_cmd_list(char ***list)
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
}

void	ft_free_vals(t_values *vals)
{
	if (vals->pids)
		free(vals->pids);
	ft_free_tokens(vals->tokens);
	ft_free_cmd_list(vals->tokens_list);
}
