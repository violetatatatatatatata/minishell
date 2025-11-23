/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token_type	ft_check_quotes(char *token, t_token_type t_type)
{
	char	quote;
	int		i;

	quote = *token;
	if (t_type != DEFAULT)
	{
		if ((t_type == DOUBLE_QUOTES && quote == '"')
			|| (t_type == SIMPLE_QUOTES && quote == '\''))
			return (DEFAULT);
		return (t_type);
	}
	i = 1;
	while (token[i])
	{
		if (token[i] == quote)
		{
			if (token[i] == '"')
				return (DOUBLE_QUOTES);
			else
				return (SIMPLE_QUOTES);
		}
		i++;
	}
	return (DEFAULT);
}
