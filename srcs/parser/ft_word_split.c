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

#include "../includes/minishell.h"

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

static void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
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

/*void	ft_word_split(char *env_var, char *prev_content, t_token **token)
{
	char	**word_split;
	int		tokens_count;
	int		i;
	char	*tmp_content;
	char	*cpy_str;

	word_split = ft_split(env_var, ' ');
	tokens_count = ft_double_arr_size(word_split);
	if (!(*token)->content)
	{
		tmp_content = ft_strjoin(prev_content, word_split[0]);
		prev_content = NULL;
		free((*token)->content);
		(*token)->content = tmp_content;
	}
	else
	{
		cpy_str = ft_strdup((*token)->content);
		free((*token)->content);
		tmp_content = ft_strjoin(cpy_str, word_split[0]);
		free(cpy_str);
		(*token)->content = tmp_content;
	}
	i = 1;
	while (i < tokens_count)
	{
		ft_add_tokentolist(word_split[i], (*token));
		(*token) = (*token)->right_side;
		i++;
	}
	}*/
