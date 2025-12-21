/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:21:07 by avelandr          #+#    #+#             */
/*   Updated: 2025/12/19 16:27:08 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_args_count(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		i++;
		token = token->right_side;
	}
	return (i);
}

void	ft_last_cmd(t_values *vals)
{
	prepare_fd_in(vals);
	vals->pids[vals->index] = fork();
	if (vals->pids[vals->index] == -1)
	{
		perror("fork");
		free(vals->pids);
		return ;
	}
	if (vals->pids[vals->index] == 0)
	{
		printf("PUTO HIJO N: %i\n", getpid());
		exec_last_child(vals);
	}
	else
	{
		ft_close_pipes(vals);
		if (vals->fd_in > 2)
			close(vals->fd_in);
		if (vals->fd_prev > 2 && vals->fd_prev != vals->fd_in)
			close(vals->fd_prev);
	}
}
