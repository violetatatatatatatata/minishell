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

static void	ft_free_tokens(t_token *token)
{
	t_token	*tmp_token;

	while (token)
	{
		tmp_token = token->right_side;
		if (token->content)
			free(token->content);
		if (token->type != WORD && token->redir)
		{
			ft_free_tokens(token->redir->redir_content);
			free(token->redir);
		}
		free(token);
		token = tmp_token;
	}
}

void	ft_free_cmd_list(t_cmd_table *table)
{
	if (!table)
		return ;
	if (table->token)
		ft_free_tokens(table->token);
	if (table->args)
		ft_free_double(table->args);
	free(table);
}
