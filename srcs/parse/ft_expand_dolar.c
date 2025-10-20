/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_dolar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_add_token(char *env_var, char ***new_tok, int current_token,
	t_token_type type)
{
	if (type == DOUBLE_QUOTES)
	{

	}
	else
	{

	}
}

static void	ft_handle_env_var(char ***new_tokens, int current_pos,
	char **current_token, char *name, t_token_type type, char **env)
{
	char	*env_var;

	env_var = ft_getenv(name, env);
	free(name);
	if (env_var)
	{
		if (type == DEFAULT)
			ft_word_split(env_var, new_tokens, current_token, current_pos);
		else
			ft_add_token(env_var, new_tokens, current_pos, type);
	}
}

void	ft_expand_dolar(char ***tokens, int current_token, char **env)
{
	char			**new_tokens;
	t_token_type	token_type;
	int				i;
	int				start;
	char			*name;

	new_tokens = NULL;
	token_type = DEFAULT;
	i = 0;
	while ((*tokens)[current_token][i])
	{
		if ((*tokens)[current_token][i] == '"'
			|| (*tokens)[current_token][i] == '\'')
			token_type = ft_check_quotes((*tokens)[current_token][i],
					token_type);
		else if ((*tokens)[current_token][i] == '$')
		{
			i++;
			if ((*tokens)[current_token][i] == '?')
			{

			}
			if ((*tokens)[current_token][i] == '{')
			{
				start = ++i;
				while (ft_isalnum((*tokens)[current_token][i])
					|| (*tokens)[current_token][i] == '_')
					i++;
				if ((*tokens)[current_token][i] == '}')
				{
					name = ft_strndup(
							(*tokens)[current_token] + start, i - start);
					ft_handle_env_var(&new_tokens, i, (*tokens)[current_token],
						name, token_type, env);
				}
			}
			if (ft_isalpha((*tokens)[current_token][i])
				|| (*tokens)[current_token][i] == '_')
			{
				start = ++i;
				while (ft_isalnum((*tokens)[current_token][i])
					|| (*tokens)[current_token][i] == '_')
					i++;
				name = ft_strndup(
						(*tokens)[current_token] + start, i - start);
				ft_handle_env_var(&new_tokens, i, (*tokens)[current_token],
					name, token_type, env);
			}
		}
		i++;
	}
}
