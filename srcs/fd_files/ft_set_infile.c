/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_infile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:38:01 by aalcaide          #+#    #+#             */
/*   Updated: 2025/08/06 16:38:29 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_exact_match(const char *line,
	const char *limiter, size_t limiter_len)
{
	size_t	i;

	i = 0;
	while (i < limiter_len)
	{
		if (line[i] != limiter[i])
			return (0);
		i++;
	}
	return (line[i] == '\n' || line[i] == '\0');
}

static int	ft_check_sig_stop(char *line, int *ret_val)
{
	if (g_status == SIGINT)
	{
		if (line)
			free(line);
		*ret_val = 130;
		return (1);
	}
	return (0);
}

static void	ft_get_text(const char *limiter, int *fd_write, int *ret_val)
{
	char	*line;
	size_t	limiter_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		printf("heredoc> ");
		line = get_next_line(STDIN_FILENO);
		printf("LINE: %s\n", line);
		if (ft_check_sig_stop(line, ret_val))
			break ;
		if (!line)
			break ;
		if (is_exact_match(line, limiter, limiter_len))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, *fd_write);
		free(line);
	}
}

int	ft_set_infile(int *fd_write,
	const char *limiter)
{
	int	ret_val;

	ret_val = 0;
	if (!limiter)
		perror("Limiter not found");
	g_status = 0;
	signals_heredoc();
	ft_get_text(limiter, fd_write, &ret_val);
	set_signals_handlers_exec();
	return (ret_val);
}
