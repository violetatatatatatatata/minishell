/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_count_cmds(char **tokens, int *num_cmds)
{
	int	i;

	*num_cmds = 1;
	i = 0;
	while (tokens[i])
	{
		if (strncmp(tokens[i], "|", 2) == 0)
			(*num_cmds)++;
		i++;
	}
}

char	**ft_tokenize(char *text, int *num_cmds, char **env)
{
	char	**tokens;
	int		num_tokens;
	int		i;

	num_tokens = ft_tokens_count(text, env);
	tokens = malloc(sizeof(char *) * (num_tokens + 1));
	printf("num: %i\n", num_tokens);
	i = 0;
	while (i < num_tokens)
	{
		tokens[i] = ft_get_token(text);
		printf("Token: %s\n", tokens[i]);
		text += ft_strlen(tokens[i]) + 1;
		i++;
	}
	tokens[num_tokens] = NULL;
	ft_count_cmds(tokens, num_cmds);
	return (tokens);
}
