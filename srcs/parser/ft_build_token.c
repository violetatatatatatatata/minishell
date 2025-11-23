/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_redir_type	ft_get_redir_type(char *str_token)
{
	if (!ft_strncmp(str_token, ">>", 2))
		return (APPEND);
	if (!ft_strncmp(str_token, ">", 1))
		return (OUTPUT);
	if (!ft_strncmp(str_token, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(str_token, "<", 1))
		return (INPUT);
	return (0);
}

t_token	*ft_build_token(char *str_token)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->content = str_token;
	token->left_side = NULL;
	token->right_side = NULL;
	token->type = WORD;
	if (ft_is_redirection(str_token))
	{
		token->type = REDIR;
		token->redir = malloc(sizeof(t_redir));
		token->redir->redir_content = NULL;
		token->redir->redir_type = ft_get_redir_type(str_token);
	}
	return (token);
}
