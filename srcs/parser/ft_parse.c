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

#include "../includes/minishell.h"

/*static void	ft_add_token(char *env_var, char *prev_str, t_token **token)
{
	char	*new_content;
	char	*tmp_content;

	printf("Add token\n");
	if (!(*token)->content)
	{
		printf("Prev_str: %s\n", prev_str);
		new_content = ft_strjoin(prev_str, env_var);
		printf("new_content: %s\n", new_content);
		(*token)->content = new_content;
	}
	else
	{
		tmp_content = ft_strjoin((*token)->content, prev_str);
		free((*token)->content);
		new_content = ft_strjoin(tmp_content, env_var);
		free(tmp_content);
		printf("Add token, existing list\n");
		(*token)->content = new_content;
	}
}*/

/*static void	ft_handle_env_var(t_token **token, char *name,
	t_quote_type type, char *prev_str, char **env)
{
	char	*env_var;
	char	*tmp_str;

	if (type == SIMPLE_QUOTES)
	{
		tmp_str = ft_strjoin("$", name);
		free(name);
		name = tmp_str;
		env_var = name;
	}
	else
		env_var = ft_getenv(name, env);
	printf("Get_env: %s\n", env_var);
	if (env_var)
	{
		printf("Valid env\n");
		if (type == DEFAULT)
			ft_word_split(env_var, prev_str, token);
		else
			ft_add_token(env_var, prev_str, token);
	}
	free(name);
}*/

/*static void	ft_expansion(char *content, t_token **token, int *index,
	int *sub_start, t_quote_type current_quote, char **env)
{
	int		start;
	int		sub_end;
	char	*name;
	char	*prev_str;

	prev_str = NULL;
	sub_end = (*index)++;
	if (sub_end > 0 && *sub_start != 0)
		sub_end--;
	if (content[*index] == '{')
	{
		start = ++(*index);
		while (ft_isalnum(content[*index])
			|| content[*index] == '_')
			(*index)++;
		if (content[*index] == '}')
		{
			name = ft_strndup(
					content + start, *index - start);
			prev_str = ft_substr(content, *sub_start, sub_end - *sub_start);
			ft_handle_env_var(token, name,
				current_quote, prev_str, env);
			*sub_start = *index + 1;
		}
	}
	if (ft_isalpha(content[*index])
		|| content[*index] == '_')
	{
		if (sub_end < 0)
			sub_end = 0;
		start = *index;
		while (ft_isalnum(content[*index])
			|| content[*index] == '_')
			(*index)++;
		name = ft_strndup(
				content + start, *index - start);
		printf("Name: %s\n", name);
		prev_str = ft_substr(content, *sub_start, sub_end - *sub_start);
		ft_handle_env_var(token, name,
			current_quote, prev_str, env);
		*sub_start = *index + 1;
		printf("Current char: %c\n", content[*index]);
		//continue ;
		(*index)--;
	}
	if (prev_str != NULL)
		free(prev_str);
		}*/

/*static void	ft_expand_dolars(t_list **cmd_list, char **env)
{
	t_list			*iter;
	t_token			*token;
	t_quote_type	current_quote;
	char			*content;
	char			*sub_str;
	char			*tmp_str;
	int				sub_start;
	int				is_expanded;
	int				i;

	iter = *cmd_list;
	while (iter)
	{
		current_quote = DEFAULT;
		token = (t_token *)iter->content;
		while (token)
		{
			is_expanded = 0;
			content = ft_strdup(token->content);
			free(token->content);
			token->content = NULL;
			sub_start = 0;
			i = 0;
			while (content[i])
			{
				if (content[i] == '"'
					|| content[i] == '\'')
					current_quote = ft_check_quotes(&content[i],
							current_quote);
				if (content[i] == '$' && content[i + 1])
				{
					is_expanded = 1;
					ft_expansion(content, &token, &i,
						&sub_start, current_quote, env);
				}
				i++;
			}
			if (!token->content && !is_expanded)
				token->content = ft_strdup(content);
			else if (token->content)
			{
				sub_str = ft_substr(content, sub_start - 1,
						ft_strlen(content) + 1 - sub_start);
				tmp_str = token->content;
				token->content = ft_strjoin(tmp_str, sub_str);
				free(tmp_str);
				free(sub_str);
			}
			token = token->right_side;
			free(content);
		}
		iter = iter->next;
	}
}*/

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
			if (token->type == REDIR)
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
		if (token->type == REDIR)
			printf("Token redir: %s\n", token->redir->redir_content->content);
		token = token->right_side;
	}
}

static void	ft_print_cmd_table(t_list *cmd_table)
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

t_list	*ft_parse(char *prompt, char **env)
{
	char	**tokens;
	t_list	*cmd_list;

	tokens = ft_tokenize(prompt);
	cmd_list = ft_split_tokens(tokens);
	ft_print_debug(cmd_list);
	printf("--------- EXPAND ---------\n");
	ft_expand_dolar(&cmd_list, env);
	ft_print_debug(cmd_list);
	printf("----- REMOVE QUOTES ------\n");
	ft_remove_quotes(cmd_list);
	ft_print_debug(cmd_list);
	cmd_list = ft_build_cmd_table(cmd_list);
	ft_print_cmd_table(cmd_list);
	printf("----- END PARSE ------\n");
	return (cmd_list);
}
