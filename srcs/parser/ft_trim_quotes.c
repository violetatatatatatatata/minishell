/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_dolar_extension	**ft_init_dolar_ext(void)
{
	t_dolar_extension	**dolar_ext;

	dolar_ext = malloc(sizeof(t_dolar_extension *));
	if (!dolar_ext)
		return (NULL);
	dolar_ext[0] = NULL;
	return (dolar_ext);
}

static void	ft_scan_token(char **token, int token_len,
		t_dolar_extension ***dolar_ext, int count_simp_quot)
{
	int	i;
	int	is_simple_quote;

	i = 0;
	is_simple_quote = 0;
	while (i < token_len)
	{
		if ((*token)[i] == '\'' && (count_simp_quot > 1
			|| (count_simp_quot > 0 && is_simple_quote)))
		{
			is_simple_quote = !is_simple_quote;
			count_simp_quot--;
		}
		else if ((*token)[i] == '$' && !is_simple_quote)
			ft_extend_dolar(&((*token)[i]), dolar_ext);
		i++;
	}
}

static void	ft_free_dolar_ext(t_dolar_extension **dolar_ext)
{
	int	i;

	i = 0;
	while (dolar_ext[i])
		free(dolar_ext[i++]);
	free(dolar_ext);
}

void	ft_trim_quotes(char **token, int token_len)
{
	t_dolar_extension	**dolar_ext;
	int					count_simp_quot;

	dolar_ext = ft_init_dolar_ext();
	if (!dolar_ext)
		return ;
	count_simp_quot = ft_count_simple_quote(*token);
	ft_scan_token(token, token_len, &dolar_ext, count_simp_quot);
	ft_change_dolar_val(token, dolar_ext);
	ft_free_dolar_ext(dolar_ext);
}
