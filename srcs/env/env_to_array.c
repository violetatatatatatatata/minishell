/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/06/02 10:55:31 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	env_count_visible(t_env *head)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->visible == 1)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	*env_join_pair(char *key, char *value)
{
	int		klen;
	int		vlen;
	char	*str;
	int		total;

	klen = strlen(key);
	vlen = 0;
	if (value != NULL)
		vlen = strlen(value);
	total = klen + vlen;
	if (value != NULL)
		total++;
	str = malloc(total + 1);
	if (!str)
		return (NULL);
	strcpy(str, key);
	if (value != NULL)
	{
		str[klen] = '=';
		strcpy(str + klen + 1, value);
	}
	return (str);
}

static int	env_fill_array(char **env, t_env *head)
{
	int		i;
	char	*str;
	t_env	*tmp;

	i = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->visible == 1)
		{
			str = env_join_pair(tmp->key, tmp->value);
			if (!str)
				return (-1);
			env[i] = str;
			i++;
		}
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (0);
}

char	**env_to_array(t_env *head)
{
	int		count;
	char	**env;
	int		status;

	count = env_count_visible(head);
	env = malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	status = env_fill_array(env, head);
	if (status == -1)
		return (NULL);
	return (env);
}
