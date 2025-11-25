/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_cmd_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/11/25 19:17:40 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list	*ft_add_cmd_table(t_token *token)
{
	t_cmd_table	*cmd_table;

	cmd_table = malloc(sizeof(t_cmd_table));
	cmd_table->token = token;
	cmd_table->args = NULL;
	return (ft_lstnew(cmd_table));
}

static int	ft_args_count(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		i++;
		token = token->right_side;
	}
	return (i);
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

static void	ft_set_args(t_list *cmd_tables)
{
	t_cmd_table	*cmd_table;
	t_token		*current_token;
	int			size;
	int			i;
	char		*str;

	while (cmd_tables)
	{
		cmd_table = (t_cmd_table *)cmd_tables->content;
		size = ft_args_count(cmd_table->token);
		cmd_table->args = malloc(sizeof(char *) * (size + 1));
		current_token = cmd_table->token;
		i = 0;
		while (i < size)
		{
			printf("CHECK %s, ", current_token->content);
			printf("TYPE %i\n", current_token->type);
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
		tmp_tokens = tokens;
		tokens = tokens->next;
		free(tmp_tokens);
	}
	ft_set_args(cmd_list);
	return (cmd_list);
}
