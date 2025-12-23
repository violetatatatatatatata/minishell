/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token	*ft_add_new_token(t_list **split_tokens, char *token_str)
{
	t_list	*new_elem;
	t_token	*token;

	new_elem = ft_lstnew(ft_build_token(token_str));
	if (!new_elem)
		return (NULL);
	ft_lstadd_back(split_tokens, new_elem);
	token = (t_token *)new_elem->content;
	return (token);
}

static void	handle_token_relation(t_token **token, char *token_str)
{
	t_token	*tmp;

	tmp = ft_build_token(token_str);
	if ((*token)->type == REDIR && !(*token)->redir->redir_content)
		(*token)->redir->redir_content = tmp;
	else
	{
		(*token)->right_side = tmp;
		*token = (*token)->right_side;
	}
}

static void	process_token(char **tokens, int *i,
				t_list **split_tokens, t_token **token)
{
	if (ft_strncmp(tokens[*i], "|", 2) == 0 || !*split_tokens)
	{
		if (ft_strncmp(tokens[*i], "|", 2) == 0)
		{
			free(tokens[*i]);
			tokens[*i] = NULL;
			(*i)++;
		}
		*token = ft_add_new_token(split_tokens, tokens[*i]);
	}
	else
		handle_token_relation(token, tokens[*i]);
}

t_list	*ft_split_tokens(char **tokens)
{
	t_list	*split_tokens;
	t_token	*token;
	int		i;

	split_tokens = NULL;
	token = NULL;
	i = 0;
	while (tokens[i])
	{
		process_token(tokens, &i, &split_tokens, &token);
		i++;
	}
	return (split_tokens);
}
