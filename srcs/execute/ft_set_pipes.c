/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:33:56 by aalcaide          #+#    #+#             */
/*   Updated: 2025/12/17 19:39:38 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	fill_pipes_aux(t_values *vals)
{
	int	i;

	i = 0;
	while (i < vals->cmds_size - 1)
	{
		vals->pipes[i] = malloc(sizeof(int) * 2);
		if (!vals->pipes[i])
		{
			ft_free_pipes(vals, vals->cmds_size - 1);
			return (print_msg(NULL, "malloc failed", EXIT_FAILURE));
		}
		if (pipe(vals->pipes[i]) == -1)
		{
			ft_free_pipes(vals, vals->cmds_size - 1);
			return (print_msg(NULL, "pipes failed", EXIT_FAILURE));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_set_pipes(t_values *vals)
{
	if (vals->cmds_size < 2)
	{
		vals->pipes = NULL;
		return (EXIT_SUCCESS);
	}
	vals->pipes = ft_calloc(vals->cmds_size - 1, sizeof(int *));
	if (!vals->pipes)
		return (print_msg(NULL, "malloc failed", EXIT_FAILURE));
	return (fill_pipes_aux(vals));
}
