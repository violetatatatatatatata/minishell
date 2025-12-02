/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_debug(t_list *cmd_list)
{
	int			i;
	t_token		*token;

	i = 0;
	while (cmd_list)
	{
		printf("--- CMD TABLE %i ---\n", i);
		token = (t_token *)cmd_list->content;
		while (token)
		{
			printf("Token: %s\n", token->content);
			if (token->type == REDIR && token->redir->redir_content)
				printf("Token redir: %s\n", token->redir->redir_content->content);
			token = token->right_side;
		}
		cmd_list = cmd_list->next;
		i++;
	}
}

void	ft_print_args_debug(char **args)
{
	int	i;

	printf("-- ARGS --\n");
	i = 0;
	while (args[i])
	{
		printf("Token args %i: %s\n", i, args[i]);
		i++;
	}
}

void	ft_print_tokens_debug(t_token *token)
{
	printf("-- TOKENS --\n");
	while (token)
	{
		printf("Token: %s\n", token->content);
		if (token->type == REDIR && token->redir->redir_content)
			printf("Token redir: %s\n", token->redir->redir_content->content);
		token = token->right_side;
	}
}

void	ft_print_cmd_table(t_list *cmd_table)
{
	t_cmd_table	*table;
	t_token		*token;

	printf("---- CMD TABLES ----\n");
	while (cmd_table)
	{
		table = (t_cmd_table *)cmd_table->content;
		token = table->token;
		ft_print_args_debug(table->args);
		ft_print_tokens_debug(token);
		cmd_table = cmd_table->next;
	}
}

t_list	*ft_parse(char *prompt, t_shell *data)
{
	char	**tokens;
	t_list	*cmd_list;

	tokens = ft_tokenize(prompt);
	cmd_list = ft_split_tokens(tokens);
	free(tokens);
	//ft_print_debug(cmd_list);
	//printf("--------- EXPAND ---------\n");
	ft_expand_dolar(&cmd_list, data);
	//ft_print_debug(cmd_list);
	//printf("----- REMOVE QUOTES ------\n");
	ft_remove_quotes(cmd_list);
	//ft_print_debug(cmd_list);
	cmd_list = ft_build_cmd_table(cmd_list);
	//ft_print_cmd_table(cmd_list);
	//printf("--------- EXPAND REDIRECTIONS ---------\n");
	ft_expand_red(cmd_list, data);
	//ft_print_cmd_table(cmd_list);
	//printf("----- END PARSE ------\n");
	return (cmd_list);
}
