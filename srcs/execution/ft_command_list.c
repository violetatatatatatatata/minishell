/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/08/07 13:23:03 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

static char	**ft_copy_tokens(char **tokens, int start, int end)
{
	char	**cmd;
	int		j;

	cmd = malloc(sizeof(char *) * (end - start + 1));
	if (!cmd)
		return (NULL);
	j = 0;
	while (j < end - start)
	{
		cmd[j] = ft_strdup(tokens[start + j]);
		j++;
	}
	cmd[j] = NULL;
	return (cmd);
}

char	***ft_command_list(t_values *vals)
{
	char	***comm_list;
	int		i;
	int		z;
	int		start;

	comm_list = malloc(sizeof(char **) * (vals->num_cmds + 1));
	if (!comm_list)
		return (NULL);
	i = 0;
	z = 0;
	start = 0;
	while (vals->tokens[i])
	{
		if (ft_strncmp(vals->tokens[i], "|", 2) == 0)
		{
			comm_list[z++] = ft_copy_tokens(vals->tokens, start, i);
			start = i + 1;
		}
		i++;
	}
	comm_list[z++] = ft_copy_tokens(vals->tokens, start, i);
	comm_list[z] = NULL;
	return (comm_list);
}
