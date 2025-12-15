/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:33:56 by aalcaide          #+#    #+#             */
/*   Updated: 2025/12/15 15:51:46 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_set_pipes(t_values *vals)
{
	int	i;

	i = 0;
	if (vals->cmds_size < 2)
	{
		vals->pipes = NULL;
		return (0);
	}
	vals->pipes = malloc(sizeof(int *) * (vals->cmds_size - 1));
	if (!vals->pipes)
		return (print_msg(NULL, "malloc failed", EXIT_FAILURE));
	while (i < vals->cmds_size - 1)
	{
		if (!vals->pipes[i])
			return (ft_free_pipes(vals, i + 1),
					print_msg(NULL, "malloc failed", EXIT_FAILURE));
		vals->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(vals->pipes[i]) == -1)
			return (ft_free_pipes(vals, i + 1),
					print_msg(NULL, "pipes failed", EXIT_FAILURE));
		i++;
	}
	return (0);
}
