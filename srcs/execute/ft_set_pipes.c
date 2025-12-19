/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:05:34 by avelandr          #+#    #+#             */
/*   Updated: 2025/12/19 16:06:31 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	create_one_pipe(t_values *vals, int i)
{
	vals->pipes[i] = malloc(sizeof(int) * 2);
	if (!vals->pipes[i])
	{
		ft_free_pipes(vals, i);
		return (print_msg(NULL, "malloc failed", EXIT_FAILURE));
	}
	if (pipe(vals->pipes[i]) == -1)
	{
		ft_free_pipes(vals, i + 1);
		return (print_msg(NULL, "pipes failed", EXIT_FAILURE));
	}
	return (0);
}

int	ft_set_pipes(t_values *vals)
{
	int	i;

	if (vals->cmds_size < 2)
	{
		vals->pipes = NULL;
		return (0);
	}
	vals->pipes = malloc(sizeof(int *) * (vals->cmds_size - 1));
	if (!vals->pipes)
		return (print_msg(NULL, "malloc failed", EXIT_FAILURE));
	i = 0;
	while (i < vals->cmds_size - 1)
	{
		if (create_one_pipe(vals, i))
			return (EXIT_FAILURE);
		i++;
	}
	return (0);
}
