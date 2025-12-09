/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:53:53 by aalcaide          #+#    #+#             */
/*   Updated: 2025/12/09 14:53:55 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_close_pipes(t_values *vals)
{
	int	i;

	i = 0;
	if (!vals || !vals->pipes)
		return ;
	while (i < vals->cmds_size - 1)
	{
		if (i != vals->index - 1)
			close(vals->pipes[i][0]);
		if (i != vals->index)
			close(vals->pipes[i][1]);
		i++;
	}
}
