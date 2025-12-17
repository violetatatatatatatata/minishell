/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 env_setandget.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/11/23 01:02:37 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/11/23 01:06:17 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <minishell.h>

t_env	*create_env_variable(char *key, char *value)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	node->visible = 1;
	node->key = ft_strdup(key);
	if (value == NULL)
		node->value = NULL;
	else
		node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	ft_setenv(t_shell *data, char *key, char *value)
{
	t_env	*current;

	current = data->env;
	if (!current)
	{
		data->env = create_env_variable(key, value);
		return ;
	}
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (value)
				already_exists(current, value);
			return ;
		}
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	current->next = create_env_variable(key, value);
}

void	already_exists(t_env *cpy, char *val)
{
	if (cpy->value)
		free(cpy->value);
	if (val == NULL)
		cpy->value = NULL;
	else
		cpy->value = ft_strdup(val);
	cpy->visible = 1;
}

// ojo pelao con el export
char	*ft_getenv(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0 && env->visible)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
