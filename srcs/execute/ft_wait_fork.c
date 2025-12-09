/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:51:48 by aalcaide          #+#    #+#             */
/*   Updated: 2025/12/09 12:51:51 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_wait_fork(pid_t pid)
{
	int		status;
	int		exit_code;
	pid_t	wpid;

	exit_code = 0;
	status = 0;
	wpid = waitpid(pid, &status, 0);
	while (wpid == -1 && errno == EINTR)
		wpid = waitpid(pid, &status, 0);
	if (wpid == -1)
		perror("waitpid");
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	return (exit_code);
}
