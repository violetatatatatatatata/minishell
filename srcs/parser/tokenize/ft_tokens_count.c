/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_one_sentence(const char *text, char c)
{
	int	i;

	i = 0;
	while (text[i] && text[i] != c)
		i++;
	if (text[i] == c)
		return (i);
	return (-1);
}

static int	ft_handle_quotes(char *text, int *i, int *count, int *is_in_word)
{
	int	num;

	num = ft_one_sentence(&text[*i + 1], text[*i]);
	if (num >= 0)
	{
		if (!*is_in_word)
		{
			*is_in_word = 1;
			(*count)++;
		}
		*i += num + 2;
		return (1);
	}
	return (0);
}

static void	ft_handle_non_quotes(char *c, int *is_in_word, int *count,
	int	*index)
{
	if (ft_is_pipe(c) || ft_is_redirection(c))
	{
		(*count)++;
		while (ft_is_redirection(c + 1))
		{
			(*index)++;
			c++;
		}
		*is_in_word = 0;
	}
	else if (!*is_in_word && !ft_isspace(*c))
	{
		*is_in_word = 1;
		(*count)++;
	}
	else if (*is_in_word && ft_isspace(*c))
		*is_in_word = 0;
}

static int	ft_process_character(t_tokens_values *tokens_vals,
	int *i,	int *is_in_word)
{
	if (tokens_vals->text[*i] == '"' || tokens_vals->text[*i] == '\'')
	{
		if (ft_handle_quotes(tokens_vals->text, i,
				&tokens_vals->count, is_in_word))
			return (1);
	}
	else
		ft_handle_non_quotes(&tokens_vals->text[*i], is_in_word,
			&tokens_vals->count, i);
	return (0);
}

int	ft_tokens_count(char *text)
{
	t_tokens_values	tokens_vals;
	int				is_in_word;
	int				i;
	int				text_len;

	i = 0;
	tokens_vals.count = 0;
	tokens_vals.text = text;
	is_in_word = 0;
	text_len = ft_strlen(text);
	while (ft_isspace(text[i]))
		i++;
	while (text[i] && text_len > i)
	{
		if (ft_process_character(&tokens_vals, &i, &is_in_word))
			continue ;
		i++;
	}
	return (tokens_vals.count);
}
