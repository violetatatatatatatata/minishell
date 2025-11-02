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

#include "../minishell.h"

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
		token->redir_content = NULL;
		token->redir_type = INPUT;
	}
	return (token);
}
