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

static void	ft_copy_before(char **tmp, char **src, int current_token)
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
}

// Cambiar esto por una funcion que modifique el char *** 
//para que contenga el token actual expandido y luego sumarlo al resto de tokens
void	ft_word_split(char *text, char ***new_tok,
	char **current_token, int pos_token)
{
	char	**word_split;
	char	**tmp;
	int		len;
	int		i;

	word_split = ft_split(text, ' ');
	len = ft_arr_size(*new_tok) + ft_arr_size(word_split);
	tmp = malloc(sizeof(char *) * (len + 1));
	if (!tmp)
		return ;
	ft_copy_before(tmp, *new_tok, current_token);
	i = current_token;
	ft_insert_split(tmp, word_split, &i);
	ft_copy_after(tmp, *new_tok, current_token, i);
	ft_free_tokens(*new_tok);
	*new_tok = tmp;
}
