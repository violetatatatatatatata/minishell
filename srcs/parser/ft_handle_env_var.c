/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_env_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/12/17 18:06:02 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_add_token(char *env_var, char *prev_str, t_token **token)
{
	char	*new_content;
	char	*tmp_content;

	if (!(*token)->content)
	{
		new_content = ft_strjoin(prev_str, env_var);
		(*token)->content = new_content;
	}
	else
	{
		tmp_content = ft_strjoin((*token)->content, prev_str);
		free((*token)->content);
		new_content = ft_strjoin(tmp_content, env_var);
		free(tmp_content);
		(*token)->content = new_content;
	}
}

static char	*ft_get_env_value(t_expand_data *data, char **name)
{
	char	*tmp;
	char	*env_var;

	env_var = NULL;
	if (data->current_quote == SIMPLE_QUOTES)
	{
		tmp = ft_strjoin("$", *name);
		free(*name);
		*name = tmp;
		env_var = *name;
	}
	else
		env_var = ft_getenv(*name, data->val->env);
	return (env_var);
}

void	ft_insert_env_value(t_expand_data *data,
	char *env_var, char *prev_str)
{
	if (!env_var)
		return ;
	if (data->current_quote == DEFAULT)
		ft_word_split(env_var, prev_str, data->token);
	else
		ft_add_token(env_var, prev_str, data->token);
}

void	ft_handle_env_var(t_expand_data *data,
	char **name, char *prev_str)
{
	char	*env_var;

	env_var = ft_get_env_value(data, name);
	if (env_var)
	{
		ft_insert_env_value(data, env_var, prev_str);
	}
}
