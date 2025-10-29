/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static int	ft_subtoken_len(char *text, int text_len)
{
	int	i;
	int	len;

	i = 0;
	while (text[i] && text_len > i)
	{
		if (text[i] == '"' || text[i] == '\'')
		{
			len = ft_one_sentence(&text[i + 1], text[i]);
			i += len + 2;
			printf("One sentence: n-%i c-%c\n", i, text[i]);
		}
		else if (!ft_isspace(text[i]))
			i++;
		else
			break ;
	}
	return (i);
}

char	*ft_get_token(char *text)
{
	char	*token;
	int		text_len;
	int		i;

	while (ft_isspace(*text))
		text++;
	text_len = ft_strlen(text);
	i = ft_subtoken_len(text, text_len);
	printf("Token size: %i\n", i);
	token = malloc(sizeof(char) * (i + 1));
	text_len = i;
	i = 0;
	while (text[i] && text_len > i)
	{
		token[i] = text[i];
		i++;
	}
	token[i] = '\0';
	printf("Get token: %s\n", token);
	/*if (ft_contains_quotes(token))
		ft_trim_quotes(&token, ft_strlen(token));
	printf("Get new token: %s\n", token);*/
	return (token);
}
