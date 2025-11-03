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

#include "../minishell.h"

/*void	ft_printf_list(char ***list)
{
	int	i;
	int	j;

	if (!list)
		return ;
	i = 0;
	while (list[i])
	{
		j = 0;
		while (list[i][j])
		{
			printf("Token: %i, Element: %i, Str: %s\n", i, j, list[i][j]);
			j++;
		}
		i++;
	}
}

static void	ft_add_integer(int **list, int new_int)
{
	int	*tmp;
	int	i;

	if (!*list)
	{
		*list = malloc(sizeof(int) * 2);
		(*list)[0] = new_int;
		(*list)[1] = -1;
		return ;
	}
	i = 0;
	while ((*list)[i] > -1)
		i++;
	tmp = malloc(sizeof(int) * (i + 2));
	i = 0;
	while ((*list)[i] > -1)
	{
		tmp[i] = (*list)[i];
		i++;
	}
	tmp[i++] = new_int;
	tmp[i] = -1;
	free(*list);
	*list = tmp;
}

static void	ft_check_env_var(int *i, int *j, char ***dolars,
	int **list_size, int *chars_count)
{
	int	size;

	size = ft_strlen(dolars[*i][*j]);
	if (!dolars[*i][*j + 1])
	{
		(*i)++;
		*j = 0;
		ft_add_integer(list_size, *chars_count + size);
		*chars_count = 0;
		if (dolars[*i][*j])
			*chars_count += ft_strlen(dolars[*i][*j]);
	}
	else
	{
		(*j)++;
		*chars_count += size;
	}
}

static char	**ft_reserve_space(char ***dolars_list, int *tok_size,
	char *token, char **env)
{
	int		i;
	int		j;
	int		dolar_j;
	int		size;
	char	**new_tok;
	int		start_dol;
	int		start_w;
	char	*name;
	char	*tmp_str;
	char	*str_tok;

	dolar_j = 0;
	i = 0;
	while (tok_size[i] > -1)
		i++;
	new_tok = malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (j < i + 1)
		new_tok[j++] = NULL;
	i = 0;
	while (tok_size[i] > -1)
	{
		new_tok[i] = NULL;
		start_w = 0;
		j = 0;
		while (token[j])
		{
			j++;
			if (token[j] == '{')
			{
				start_dol = ++j;
				while (ft_isalnum(token[j])
					|| token[j] == '_')
					j++;
				if (token[j] == '}')
				{
					name = ft_strndup(
							token + start_dol, j - start_dol);
					if (ft_isvalid_envvar(name, env))
					{
						tmp_str = ft_substr(token, start_w, start_dol - 3);
						str_tok = ft_strjoin
							(tmp_str, dolars_list[i][dolar_j++]);
						free(tmp_str);
						tmp_str = ft_strjoin(new_tok[i], str_tok);
						free(new_tok[i]);
						new_tok[i] = tmp_str;
						if (!dolars_list[i][dolar_j++] && dolars_list[i + 1])
						{
							new_tok[i + 1] = ft_strdup(dolars_list[i + 1][0]);
							dolar_j = 1;
						}
					}
					free(name);
					start_w = j + 1;
				}
			}
			if (ft_isalpha(token[j])
				|| token[j] == '_')
			{
				start_dol = j;
				while (ft_isalnum(token[j])
					|| token[j] == '_')
					j++;
				name = ft_strndup(
						token + start_dol, j - start_dol);
				if (ft_isvalid_envvar(name, env))
				{
					size = start_dol - 2;
					if (size < 0)
						size = 0;
					tmp_str = ft_substr(token, start_w, size);
					printf("tmp_str: %s char: %i dolar: %s\n", tmp_str, j, dolars_list[i][dolar_j]);
					str_tok = ft_strjoin
						(tmp_str, dolars_list[i][dolar_j++]);
					free(tmp_str);
					tmp_str = ft_strjoin(new_tok[i], str_tok);
					free(new_tok[i]);
					new_tok[i] = tmp_str;
					if (!dolars_list[i][dolar_j++] && dolars_list[i + 1])
					{
						new_tok[i + 1] = ft_strdup(dolars_list[i + 1][0]);
						dolar_j = 1;
					}
				}
				free(name);
				start_w = j + 1;
				continue ;
			}
			j++;
		}
		i++;
	}
	return (new_tok);
}

static int	*ft_add_tokens(char *token, char ***dolars,
	char **env)
{
	int				i;
	int				start_dol;
	int				chars_count;
	char			*name;
	int				*list_size;
	int				dolar_i;
	int				dolar_j;

	dolar_i = 0;
	dolar_j = 0;
	chars_count = 0;
	i = 0;
	list_size = NULL;
	while (token[i])
	{
		if (token[i] == '$')
		{
			i++;
			if (token[i] == '{')
			{
				start_dol = ++i;
				while (ft_isalnum(token[i])
					|| token[i] == '_')
					i++;
				if (token[i] == '}')
				{
					name = ft_strndup(
							token + start_dol, i - start_dol);
					if (ft_isvalid_envvar(name, env))
					{
						ft_check_env_var(&dolar_i, &dolar_j, dolars,
							&list_size, &chars_count);
					}
				}
			}
			if (ft_isalpha(token[i])
				|| token[i] == '_')
			{
				start_dol = i;
				while (ft_isalnum(token[i])
					|| token[i] == '_')
					i++;
				name = ft_strndup(
						token + start_dol, i - start_dol);
				if (ft_isvalid_envvar(name, env))
				{
					ft_check_env_var(&dolar_i, &dolar_j, dolars,
						&list_size, &chars_count);
				}
				continue ;
			}
		}
		i++;
		chars_count++;
	}
	ft_add_integer(&list_size, chars_count);
	return (list_size);
}*/

/*static void	ft_addtotoken_list(char ***tok_list, char **)
{

}*/

/*void	ft_parse(t_values *values)
{
	int		i;
	int		j;
	char	***dolars_list;
	int		*tok_size;
	char	**tmp_tok;

	printf("Parse!\n");
	dolars_list = NULL;
	tmp_tok = NULL;
	i = 0;
	while (values->tokens[i])
	{
		dolars_list = ft_expand_dolar(values->tokens[i], values->env);
		ft_printf_list(dolars_list);
		tok_size = ft_add_tokens(values->tokens[i], dolars_list, values->env);
		j = 0;
		while (tok_size[j] > -1)
		{
			printf("New size: %i\n", tok_size[j]);
			j++;
		}
		tmp_tok = ft_reserve_space(dolars_list, tok_size, values->tokens[i],
				values->env);
		j = 0;
		while (tmp_tok[j])
		{
			printf("New tokens parse: %s\n", tmp_tok[j]);
			j++;
		}
		i++;
		free(tok_size);
		ft_free_triple(dolars_list);
	}
	ft_exec_cmd_line(values);
	i = 0;
	while (values->tokens[i])
	{
		printf("Token final: %s of %i\n", values->tokens[i], i);
		i++;
	}
}*/

static void	ft_add_token(char *env_var, char *prev_str, t_token **token)
{
	char	*new_content;
	char	*tmp_content;

	printf("Add token\n");
	if (!(*token)->content)
	{
		printf("Prev_str: %s", prev_str);
		new_content = ft_strjoin(prev_str, env_var);
		printf("new_content: %s", new_content);
		free(prev_str);
		prev_str = NULL;
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
}

static void	ft_handle_env_var(t_token **token, char *name,
	t_quote_type type, char *prev_str, char **env)
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
			ft_word_split(env_var, prev_str, token);
		else
			ft_add_token(env_var, prev_str, token);
	}
	free(name);
}

static void	ft_expansion(char *content, t_token **token, int *index,
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
}

static void	ft_expand_dolars(t_list **cmd_list, char **env)
{
	t_list			*iter;
	t_token			*token;
	t_quote_type	current_quote;
	char			*content;
	int				sub_start;
	int				is_expanded;
	int				i;

	iter = *cmd_list;
	while (iter)
	{
		is_expanded = 0;
		current_quote = DEFAULT;
		token = (t_token *)iter->content;
		while (token)
		{
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
			token = token->right_side;
			free(content);
		}
		iter = iter->next;
	}
}

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
				printf("Token redir: %s\n", token->redir_content->content);
			token = token->right_side;
		}
		cmd_list = cmd_list->next;
		i++;
	}
}

void	ft_parse(char *prompt, char **env)
{
	char	**tokens;
	t_list	*cmd_list;

	tokens = ft_tokenize(prompt);
	cmd_list = ft_split_tokens(tokens);
	ft_print_debug(cmd_list);
	printf("---------------------\n");
	ft_expand_dolars(&cmd_list, env);
	ft_print_debug(cmd_list);
	cmd_list = ft_build_cmd_table(cmd_list);
}
