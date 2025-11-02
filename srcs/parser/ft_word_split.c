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

#include "../minishell.h"

/*static void	ft_copy_before(char **tmp, char **src, int current_token)
{
	int	i;

	i = 0;
	while (i < current_token)
	{
		tmp[i] = ft_strdup(src[i]);
		i++;
	}
}

static void	ft_copy_after(char **tmp, char **src, int current_token, int start)
{
	int	i;
	int	j;

	i = start;
	j = current_token + 1;
	while (src[j])
	{
		tmp[i] = ft_strdup(src[j]);
		i++;
		j++;
	}
	tmp[i] = NULL;
}

static void	ft_insert_split(char **tmp, char **word_split, int *i)
{
	int	j;

	j = 0;
	while (word_split[j])
	{
		tmp[*i] = ft_strdup(word_split[j]);
		(*i)++;
		j++;
	}
}*/

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

/*void	ft_word_split(char *env_var, char ****dolars_ex)
{
	char	**word_split;
	char	***tmp;
	int		dolars_len;
	int		arr_len;
	int		tokens_count;
	int		w_count;
	int		i;
	int		j;

	printf("world_split\n");
	word_split = ft_split(env_var, ' ');
	tokens_count = ft_double_arr_size(word_split);
	if (!*dolars_ex)
		return (ft_first_expansion(dolars_ex, word_split, tokens_count));
	dolars_len = ft_triple_arr_size(*dolars_ex);
	tmp = malloc(sizeof(char **) * (dolars_len + tokens_count));
	i = 0;
	printf("Error1\n");
	while ((*dolars_ex)[i + 1])
	{
		tmp[i] = ft_dup_tokens((*dolars_ex)[i]);
		i++;
	}
	if (i > 0)
		i--;
	printf("Error2\n");
	arr_len = ft_double_arr_size((*dolars_ex)[i]);
	printf("Error3.1\n");
	tmp[i] = malloc(sizeof(char *) * (arr_len + 2));
	j = 0;
	while ((*dolars_ex)[i][j])
	{
		tmp[i][j] = ft_strdup((*dolars_ex)[i][j]);
		j++;
	}
	printf("Error3.2\n");
	tmp[i][j] = ft_strdup(word_split[0]);
	tmp[i][++j] = NULL;
	w_count = 1;
	printf("Error4\n");
	while (w_count < tokens_count)
	{
		tmp[i + w_count] = malloc(sizeof(char *) * 2);
		tmp[i + w_count][0] = ft_strdup(word_split[w_count]);
		tmp[i + w_count][1] = NULL;
		w_count++;
	}
	tmp[i + w_count] = NULL;
	printf("Free word_split\n");
	ft_free_triple(*dolars_ex);
	ft_free_double(word_split);
	*dolars_ex = tmp;
}*/

static void	ft_add_token(char *content, t_token *token)
{
	t_token	*prev_token;
	t_token	*new_token;

	prev_token = token->right_side;
	new_token = ft_build_token(content);
	token->right_side = new_token;
	new_token->right_side = prev_token;
}

void	ft_word_split(char *env_var, char *prev_content, t_token **token)
{
	char	**word_split;
	int		tokens_count;
	int		i;
	char	*tmp_content;

	word_split = ft_split(env_var, ' ');
	tokens_count = ft_double_arr_size(word_split);
	tmp_content = ft_strjoin(prev_content, word_split[0]);
	free((*token)->content);
	(*token)->content = tmp_content;
	i = 1;
	while (i < tokens_count)
	{
		ft_add_token(word_split[i], (*token));
		(*token) = (*token)->right_side;
		i++;
	}
}
