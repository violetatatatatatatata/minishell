<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 01:09:26 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/23 01:10:13 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// tema doble frees
void	free_node(t_env *node)
{
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	create_node(t_env *node, char *key, char *value, int state)
{
	node->key = key;
	node->value = value;
	node->visible = state;
	node->next = NULL;
}

void	ft_lstclear_env(t_env **lst)
{
	t_env	*current;
	t_env	*tmp;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		tmp = current->next;
		free_node(current);
		current = tmp;
	}
	*lst = NULL;
}

char	*ft_getkey(char *line, char *eq_pos)
{
	return (ft_substr(line, 0, (eq_pos - line)));
}

char	*ft_getvalue(char *eq_pos)
{
	return (ft_strdup(eq_pos + 1));
=======
#include <minishell.h>

t_env	*create_env_variable(char *key, char *value)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	if (node)
		create_node(node, ft_strdup(key), ft_strdup(value), 1);
	return (node);
}

void	ft_setenv(t_shell *data, char *key, char *value)
{
	t_env	*current;

	current = data->env;
	while (current->next != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	if (current)
		current->next = create_env_variable(key, value);
	else
		data->env = create_env_variable(key, value);    // lista vacía
}

char	*ft_getenv(const char *key, t_env *env)
{
	while (env)
	{
		if ((ft_strcmp(env->key, (char *)key) == 0) && env->visible)
			return (env->value);
		env = env->next;
	}
	return (NULL);
>>>>>>> 4e010f65a06e4435fcfc68b687145507eb73604f
}
