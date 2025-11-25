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

static void	ft_join_first_token(char *prev_content, char **word_split,
		t_token **token)
{
	char	*tmp_content;
	char	*cpy_str;

	if (!(*token)->content)
	{
		tmp_content = ft_strjoin(prev_content, word_split[0]);
		free((*token)->content);
		(*token)->content = tmp_content;
	}
	else
	{
		cpy_str = ft_strdup((*token)->content);
		free((*token)->content);
		tmp_content = ft_strjoin(cpy_str, prev_content);
		free(cpy_str);
		cpy_str = ft_strjoin(tmp_content, word_split[0]);
		free(tmp_content);
		(*token)->content = cpy_str;
	}
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

void	ft_word_split(char *env_var, char *prev_content, t_token **token)
{
	char	**word_split;
	int		tokens_count;

	printf("WORD SPLIT\n");
	word_split = ft_split(env_var, ' ');
	if (!word_split)
	{
		printf("WORD SPLIT NULL, prev: %s\n", prev_content);
		if (prev_content && ft_strlen(prev_content) > 0)
			(*token)->content = ft_strdup(prev_content);
		else
		{
			(*token)->content = malloc(1);
			(*token)->content[0] = '\0';
		}
		return ;
	}
	tokens_count = ft_double_arr_size(word_split);
	printf("Tokens count %i\n", tokens_count);
	if (tokens_count == 0)
		return ;
	ft_join_first_token(prev_content, word_split, token);
	if (tokens_count > 1)
		ft_add_remaining_tokens(word_split, tokens_count, token);
	ft_free_split(word_split);
}
