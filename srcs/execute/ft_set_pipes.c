/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:33:56 by aalcaide          #+#    #+#             */
/*   Updated: 2025/12/09 14:33:59 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_set_pipes(t_values *vals)
{
	int	i;

	i = 0;
	vals->pipes = malloc(sizeof(int *) * (vals->cmds_size) - 1);
	while (i < vals->cmds_size - 1)
	{
		vals->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(vals->pipes[i]) == -1)
			return (ft_free_pipes(vals, i + 1), perror("Pipe"), 1);
		i++;
	}
	return (0);
}
