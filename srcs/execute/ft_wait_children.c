/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_children.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/06/02 10:55:31 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_wait_children(int num_cmds, pid_t *pids)
{
	int		i;
	int		status;
	int		exit_code;
	pid_t	wpid;

	exit_code = 0;
	status = 0;
	i = 0;
	while (i < num_cmds - 1)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	wpid = waitpid(pids[num_cmds - 1], &status, 0);
	while (wpid == -1 && errno == EINTR)
		wpid = waitpid(pids[num_cmds - 1], &status, 0);
	if (wpid == -1)
		perror("waitpid");
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	free(pids);
	return (exit_code);
}
