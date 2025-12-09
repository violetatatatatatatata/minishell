/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:43:50 by aalcaide          #+#    #+#             */
/*   Updated: 2025/12/09 14:43:52 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_pipes(t_values *vals, int size)
{
	int	i;

	i = 0;
	if (!vals || !vals->pipes)
		return ;
	while (i < size)
	{
		if (vals->pipes[i])
		{
			close(vals->pipes[i][0]);
			close(vals->pipes[i][1]);
			free(vals->pipes[i]);
		}
		i++;
	}
	free(vals->pipes);
	vals->pipes = NULL;
}
