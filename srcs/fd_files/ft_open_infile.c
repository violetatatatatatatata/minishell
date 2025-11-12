/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_infile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:15:59 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/01 13:16:04 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_search_open_file(t_redir_type type)
{
	if (type == HEREDOC)
		return (1);
	else if (type == INPUT)
		return (2);
	return (0);
}

static int	ft_open_fdin(char *str)
{
	int		fd_in;

	fd_in = open(str, O_RDONLY);
	if (fd_in < 0)
	{
		perror(str);
		fd_in = open("/dev/null", O_RDONLY);
	}
	return (fd_in);
}

static int	ft_handle_heredoc(char *str_lim)
{
	char	*limiter;
	int		fd_in;

	fd_in = -1;
	limiter = ft_strdup(str_lim);
	ft_here_doc(&fd_in, limiter);
	free(limiter);
	return (fd_in);
}

static void	ft_open_infile_type(t_token *token, int *fd_in)
{
	int	result;

	result = 0;
	result = ft_search_open_file(token->redir->redir_type);
	if (result == 1)
	{
		if (*fd_in > 2)
			close(*fd_in);
		*fd_in = ft_handle_heredoc(token->redir->redir_content->content);
	}
	else if (result == 2)
	{
		if (*fd_in > 2)
			close(*fd_in);
		*fd_in = ft_open_fdin(token->redir->redir_content->content);
	}
}

int	ft_open_infile(t_token *token)
{
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (token)
	{
		if (token->type == WORD)
		{
			token = token->right_side;
			continue ;
		}
		ft_open_infile_type(token, &fd_in);
		token = token->right_side;
	}
	return (fd_in);
}
