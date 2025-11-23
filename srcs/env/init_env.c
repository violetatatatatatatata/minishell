/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 01:00:06 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/23 01:01:50 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_env	*env_nodes(char *line)
{
	t_env	*new_node;
	char	*separator;
	char	*key;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	separator = ft_strchr(line, '=');
	if (!separator)
		create_node(new_node, ft_strdup(line), NULL, 0);
	else
	{
		key = ft_getkey(line, separator);
		create_node(new_node, key, ft_getvalue(separator), 1);
	}
	new_node->next = NULL;
	if (!new_node->key || (separator != NULL && !new_node->value))
	{
		free_node(new_node);
		return (NULL);
	}
	return (new_node);
}

t_env	*init_env(char **env)
{
	t_env	*head;
	t_env	*current_position;
	t_env	*new;
	int		i;

	i = -1;
	head = NULL;
	current_position = NULL;
	while (env[++i])
	{
		new = env_nodes(env[i]);
		if (!new)
			return (NULL);
		if (head == NULL)
			head = new;
		else
			current_position->next = new;
		current_position = new;
	}
	return (head);
}

void	handle_missing_env(t_shell *data, char *name)
{
	char	buff[PATH_MAX];

	data->env = create_env_variable("SHLVL", "1");
	if (data->env && getcwd(buff, PATH_MAX))
		data->env->next = create_env_variable("PWD", buff);
	if (data->env && data->env->next)
		data->env->next->next = create_env_variable("_", name);
}
