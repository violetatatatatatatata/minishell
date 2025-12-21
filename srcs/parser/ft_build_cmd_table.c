/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_cmd_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:13:19 by avelandr          #+#    #+#             */
/*   Updated: 2025/12/19 16:23:36 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_list	*ft_add_cmd_table(t_token *token)
{
	t_cmd_table	*cmd_table;

	cmd_table = malloc(sizeof(t_cmd_table));
	cmd_table->token = token;
	cmd_table->args = NULL;
	return (ft_lstnew(cmd_table));
}

static char	*ft_check_null_char(char *token)
{
	char	*str;
	int		len;

	if (!token)
		return (NULL);
	len = ft_strlen(token);
	if (len == 0)
	{
		str = malloc(1);
		str[0] = '\0';
		return (str);
	}
	str = ft_strdup(token);
	return (str);
}

static void	fill_cmd_args(t_cmd_table *cmd_table, int size)
{
	t_token	*current_token;
	char	*str;
	int		i;

	current_token = cmd_table->token;
	i = 0;
	while (i < size)
	{
		if (!current_token->content || current_token->type == REDIR)
		{
			current_token = current_token->right_side;
			size--;
			continue ;
		}
		str = ft_check_null_char(current_token->content);
		cmd_table->args[i++] = str;
		current_token = current_token->right_side;
	}
	cmd_table->args[i] = NULL;
}

static void	ft_set_args(t_list *cmd_tables)
{
	t_cmd_table	*cmd_table;
	int			size;

	while (cmd_tables)
	{
		cmd_table = (t_cmd_table *)cmd_tables->content;
		size = ft_args_count(cmd_table->token);
		cmd_table->args = malloc(sizeof(char *) * (size + 1));
		if (cmd_table->args)
			fill_cmd_args(cmd_table, size);
		cmd_tables = cmd_tables->next;
	}
}

t_list	*ft_build_cmd_table(t_list *tokens)
{
	t_list	*cmd_list;
	t_list	*tmp_tokens;
	t_token	*token;

	cmd_list = NULL;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		ft_lstadd_back(&cmd_list, ft_add_cmd_table(token));
		tmp_tokens = tokens->next;
		free(tokens);
		tokens = tmp_tokens;
	}
	ft_set_args(cmd_list);
	return (cmd_list);
}
