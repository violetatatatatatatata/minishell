/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/08/07 13:23:03 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*static void	ft_child_content(int *fd_pipe, const char *limiter)
{
	close(fd_pipe[0]);
	printf("Limiter: %s\n", limiter);
	ft_set_infile(&fd_pipe[1], limiter);
	close(fd_pipe[1]);
	exit(EXIT_SUCCESS);
}

void	ft_here_doc(int *fd_in,
	const char *limiter)
{
	int		fd_pipe[2];
	pid_t	child;

	if (pipe(fd_pipe) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	child = fork();
	if (child == -1)
	{
		perror("Couldn't create child");
		exit(EXIT_FAILURE);
	}
	if (child == 0)
		ft_child_content(fd_pipe, limiter);
	else
	{
		close(fd_pipe[1]);
		*fd_in = fd_pipe[0];
		waitpid(child, NULL, 0);
	}
}*/

void	ft_here_doc(int *fd_in,
	const char *limiter)
{
	int	fd_pipe[2];

	if (pipe(fd_pipe) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	ft_set_infile(&fd_pipe[1], limiter);
	close(fd_pipe[1]);
	*fd_in = fd_pipe[0];
}
