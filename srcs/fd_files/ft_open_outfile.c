/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_outfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:15:59 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/01 13:16:04 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_search_file(t_redir_type type)
{
	printf("TYPE TOKEN: %i\n", type);
	if (type == OUTPUT)
		return (1);
	else if (type == APPEND)
		return (2);
	return (0);
}

static int	ft_open_output_file(char *filename, int mode, int *ret_val)
{
	int	fd_out;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (mode == 1)
		flags |= O_TRUNC;
	else
		flags |= O_APPEND;
	fd_out = open(filename, flags, 0644);
	if (fd_out < 0)
		if (access(filename, W_OK) == 0)
			*ret_val = print_msg(NOT_PERMISSION_MSG, filename, 1);
	return (fd_out);
}

int	ft_open_outfile(t_token *token, int *ret_val)
{
	int	mode;
	int	fd_out;

	fd_out = STDOUT_FILENO;
	while (token)
	{
		if (token->type == WORD)
		{
			token = token->right_side;
			continue ;
		}
		mode = ft_search_file(token->redir->redir_type);
		if (mode == 1 || mode == 2)
			fd_out = ft_open_output_file(token->redir->redir_content->content,
					mode, ret_val);
		token = token->right_side;
	}
	return (fd_out);
}
