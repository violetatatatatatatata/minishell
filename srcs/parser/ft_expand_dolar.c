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

#include "../../includes/minishell.h"

static void	ft_finalize_token_expansion(t_token *token,
		char *content, int sub_start, int is_expanded)
{
	char	*sub_str;
	char	*tmp_str;

	if (!token->content && !is_expanded)
		token->content = ft_strdup(content);
	else if (token->content)
	{
		sub_str = ft_substr(content, sub_start - 1,
				ft_strlen(content) + 1 - sub_start);
		tmp_str = token->content;
		token->content = ft_strjoin(tmp_str, sub_str);
		if (tmp_str)
			free(tmp_str);
		if (sub_str)
			free(sub_str);
	}
}

static void	ft_process_char(t_process_vars *v, t_expand_data *data,
	char *content)
{
	if (content[v->i] == '"' || content[v->i] == '\'')
		v->current_quote = ft_check_quotes(&content[v->i], v->current_quote);
	if (content[v->i] == '$' && content[v->i + 1]
		&& (ft_isalnum(content[v->i + 1]) || content[v->i + 1] == '_'
			|| content[v->i + 1] == '{' || content[v->i + 1] == '?'))
	{
		v->is_expanded = 1;
		data->content = content;
		data->index = &v->i;
		data->sub_start = &v->sub_start;
		data->current_quote = v->current_quote;
		ft_expansion(data);
	}
}

static void	ft_process_content(char *content, t_token *token, t_shell *dat_env)
{
	t_process_vars	v;
	t_expand_data	data;

	v.current_quote = DEFAULT;
	v.is_expanded = 0;
	v.sub_start = 0;
	v.i = 0;
	data.val = dat_env;
	data.exit_status = &dat_env->exit_status;
	data.token = &token;
	while (content[v.i])
	{
		ft_process_char(&v, &data, content);
		v.i++;
	}
	ft_finalize_token_expansion(token, content, v.sub_start, v.is_expanded);
}

void	ft_expand_token_list(t_token *token, t_shell *data)
{
	char	*content;

	while (token)
	{
		content = ft_strdup(token->content);
		free(token->content);
		token->content = NULL;
		ft_process_content(content, token, data);
		free(content);
		token = token->right_side;
	}
}

void	ft_expand_dolar(t_list **cmd_list, t_shell *data)
{
	t_list	*iter;
	t_token	*token;

	iter = *cmd_list;
	while (iter)
	{
		token = (t_token *)iter->content;
		ft_expand_token_list(token, data);
		iter = iter->next;
	}
}
