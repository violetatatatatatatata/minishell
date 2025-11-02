/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/08/07 13:23:03 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_pipes(char *prompt)
{
	int	i;
	int	is_pipe;

	i = 0;
	while (ft_isspace(prompt[i]))
		i++;
	if (prompt[i] == '|')
		return (FALSE);
	while (prompt[i])
	{
		if (prompt[i] == '|')
		{
			if (is_pipe)
				return (FALSE);
			is_pipe = 1;
		}
		else if (!ft_isspace(prompt[i]))
			is_pipe = 0;
		i++;
	}
	return (!is_pipe);
}

static int	ft_check_quotes_prompt(char *prompt)
{
	t_quote_type	type;
	int				i;

	type = DEFAULT;
	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '"')
		{
			if (type == DEFAULT)
				type = DOUBLE_QUOTES;
			else if (type == DOUBLE_QUOTES)
				type = DEFAULT;
		}
		else if (prompt[i] == '\'')
		{
			if (type == DEFAULT)
				type = SIMPLE_QUOTES;
			else if (type == SIMPLE_QUOTES)
				type = DEFAULT;
		}
		i++;
	}
	return (type == DEFAULT);
}

static int	ft_check_redirections(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '>' || prompt[i] == '<')
		{
			if (prompt[i] == prompt[i + 1])
				i++;
			i++;
			while (ft_isspace(prompt[i]))
				i++;
			if (prompt[i] == '>' || prompt[i] == '<' || prompt[i] == '|'
				|| prompt[i] == '\0')
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	ft_lexer(char *prompt)
{
	if (ft_strlen(prompt) == 0)
		return (FALSE);
	else if (ft_check_pipes(prompt) == FALSE)
		return (FALSE);
	else if (ft_check_quotes_prompt(prompt) == FALSE)
		return (FALSE);
	else if (ft_check_redirections(prompt) == FALSE)
		return (FALSE);
	return (TRUE);
}
