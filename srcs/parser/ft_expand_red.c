/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_expand_red(t_list *cmd_list, t_shell *data)
{
	t_cmd_table		*table;
	t_token			*token;

	while (cmd_list)
	{
		table = (t_cmd_table *)cmd_list->content;
		token = table->token;
		while (token)
		{
			if (token->type == REDIR)
			{
				ft_expand_token_list(token->redir->redir_content, data);
				ft_process_token_list(token->redir->redir_content);
			}
			token = token->right_side;
		}
		cmd_list = cmd_list->next;
	}
}
