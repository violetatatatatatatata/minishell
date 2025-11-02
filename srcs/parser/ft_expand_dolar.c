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

static void	ft_add_token(char *env_var, char ****dolars_ex)
{
	char	***tmp_con;
	int		arr_size;
	int		i;
	int		j;

	printf("Add token\n");
	if (!*dolars_ex)
	{
		*dolars_ex = malloc(sizeof(char **) * 2);
		(*dolars_ex)[0] = malloc(sizeof(char *) * 2);
		(*dolars_ex)[0][0] = ft_strdup(env_var);
		(*dolars_ex)[0][1] = NULL;
		(*dolars_ex)[1] = NULL;
	}
	else
	{
		printf("Add token, existing list\n");
		arr_size = ft_triple_arr_size(*dolars_ex);
		tmp_con = malloc(sizeof(char **) * (arr_size + 1));
		i = 0;
		while (i < arr_size && (*dolars_ex)[i + 1])
		{
			tmp_con[i] = ft_dup_tokens((*dolars_ex)[i]);
			i++;
		}
		tmp_con[i + 1] = NULL;
		arr_size = ft_double_arr_size((*dolars_ex)[i]);
		tmp_con[i] = malloc(sizeof(char *) * (arr_size + 2));
		j = 0;
		while (j < arr_size)
		{
			tmp_con[i][j] = ft_strdup((*dolars_ex)[i][j]);
			j++;
		}
		tmp_con[i][j] = ft_strdup(env_var);
		tmp_con[i][j + 1] = NULL;
		ft_free_triple(*dolars_ex);
		*dolars_ex = tmp_con;
	}
}

// Solucionar que cuando sea comillas simples meter dolar el principio
static void	ft_handle_env_var(char ****dolars_ex, char *name,
	t_quote_type type, char **env)
{
	char	*env_var;

	if (type == SIMPLE_QUOTES)
		env_var = name;
	else
		env_var = ft_getenv(name, env);
	printf("Get_env: %s\n", env_var);
	if (env_var)
	{
		printf("Valid env\n");
		if (type == DEFAULT)
			ft_word_split(env_var, dolars_ex);
		else
			ft_add_token(env_var, dolars_ex);
	}
	free(name);
}

char	***ft_expand_dolar(char *tokens, char **env)
{
	char			***dolars_ex;
	t_quote_type	token_type;
	int				i;
	int				start;
	char			*name;

	dolars_ex = NULL;
	token_type = DEFAULT;
	i = 0;
	while (tokens[i])
	{
		printf("char: %c\n", tokens[i]);
		if (tokens[i] == '"'
			|| tokens[i] == '\'')
			token_type = ft_check_quotes(&tokens[i],
					token_type);
		else if (tokens[i] == '$')
		{
			i++;
			if (tokens[i] == '?')
			{

			}
			if (tokens[i] == '{')
			{
				start = ++i;
				while (ft_isalnum(tokens[i])
					|| tokens[i] == '_')
					i++;
				if (tokens[i] == '}')
				{
					name = ft_strndup(
							tokens + start, i - start);
					ft_handle_env_var(&dolars_ex, name,
						token_type, env);
				}
			}
			if (ft_isalpha(tokens[i])
				|| tokens[i] == '_')
			{
				start = i;
				while (ft_isalnum(tokens[i])
					|| tokens[i] == '_')
					i++;
				name = ft_strndup(
						tokens + start, i - start);
				printf("Name: %s\n", name);
				ft_handle_env_var(&dolars_ex, name,
					token_type, env);
				printf("Current char: %c\n", tokens[i]);
				continue ;
			}
		}
		i++;
	}
	return (dolars_ex);
}
