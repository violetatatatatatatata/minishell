/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_free_token(t_token *token)
{
	t_token	*tmp_token;

	while (token)
	{
		free(token->content);
		if (token->type != WORD && token->redir)
		{
			ft_free_token(token->redir->redir_content);
			free(token->redir);
		}
		tmp_token = token;
		token = token->right_side;
		free(tmp_token);
	}
}

void	ft_free_cmd_list(t_cmd_table *table)
{
	t_token	*token;

	token = table->token;
	ft_free_token(token);
	free(table);
}
