/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_copy_without_quotes(const char *src, char *dst)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (src[i])
	{
		if (src[i] == '\'' || src[i] == '"')
		{
			if (quote == 0)
				quote = src[i];
			else if (src[i] == quote)
				quote = 0;
			else
				dst[j++] = src[i];
		}
		else
			dst[j++] = src[i];
		i++;
	}
	dst[j] = '\0';
}

static char	*ft_strip_quotes(const char *src)
{
	char	*dst;
	size_t	len;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	ft_copy_without_quotes(src, dst);
	return (dst);
}

void	ft_process_token_list(t_token *token)
{
	char	*new_str;

	while (token)
	{
		new_str = ft_strip_quotes(token->content);
		if (new_str)
		{
			free(token->content);
			token->content = new_str;
		}
		token = token->right_side;
	}
}

void	ft_remove_quotes(t_list *cmd_list)
{
	t_token	*token;

	while (cmd_list)
	{
		token = (t_token *)cmd_list->content;
		ft_process_token_list(token);
		cmd_list = cmd_list->next;
	}
}
