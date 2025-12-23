/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_first_expansion(char ****dolars_ex,
	char **word_split, int tokens_count)
{
	int		i;
	char	***tmp;

	tmp = malloc(sizeof(char **) * (tokens_count + 1));
	if (!tmp)
		return ;
	i = 0;
	while (i < tokens_count)
	{
		tmp[i] = malloc(sizeof(char *) * 2);
		tmp[i][0] = ft_strdup(word_split[i]);
		tmp[i][1] = NULL;
		i++;
	}
	tmp[i] = NULL;
	ft_free_double(word_split);
	*dolars_ex = tmp;
	return ;
}

static void	ft_join_first_token(char *prev_str, char *word_split,
		t_token **token, int expansion_size)
{
	char	*tmp;

	if (!(*token)->content)
	{
		tmp = ft_strjoin(prev_str, word_split);
		(*token)->content = tmp;
	}
	else
	{
		tmp = ft_strjoin((*token)->content, prev_str);
		free((*token)->content);
		(*token)->content = ft_strjoin(tmp, word_split);
		free(tmp);
	}
	(*token)->expand_size = expansion_size;
}

static void	ft_add_remaining_tokens(char **word_split, int tokens_count,
		t_token **token)
{
	int	i;

	i = 1;
	while (i < tokens_count)
	{
		ft_add_tokentolist(word_split[i], *token);
		*token = (*token)->right_side;
		i++;
	}
}

static void	ft_handle_no_split(char *prev_content, t_token **token)
{
	if (prev_content && ft_strlen(prev_content) > 0)
		(*token)->content = ft_strdup(prev_content);
	else
	{
		(*token)->content = malloc(1);
		(*token)->content[0] = '\0';
	}
}

void	ft_word_split(char *env_var, char *prev_content, t_token **token)
{
	char	**word_split;
	int		tokens_count;
	char	*tmp;

	word_split = NULL;
	if (env_var)
		word_split = ft_split(env_var, ' ');
	if (!word_split)
	{
		ft_handle_no_split(prev_content, token);
		return ;
	}
	tokens_count = ft_double_arr_size(word_split);
	if (tokens_count == 0)
	{
		ft_free_split(word_split);
		(*token)->expand_size = tokens_count;
		if (env_var[0] == ' ' && (!prev_content || prev_content[0] == '\0'))
			ft_join_first_token(prev_content, NULL, token, tokens_count);
		else
		{
			tmp = ft_strdup(" ");
			ft_join_first_token(prev_content, tmp, token, tokens_count);
			free(tmp);
		}
		return ;
	}
	ft_join_first_token(prev_content, word_split[0], token, tokens_count);
	if (tokens_count > 1)
		ft_add_remaining_tokens(word_split, tokens_count, token);
	ft_free_split(word_split);
}
