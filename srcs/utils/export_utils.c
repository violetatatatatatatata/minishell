/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 01:15:44 by avelandr          #+#    #+#             */
/*   Updated: 2025/12/15 14:26:26 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	swap_env_nodes(t_env *a, t_env *b)
{
	t_env	tmp;

	tmp.key = a->key;
	tmp.value = a->value;
	tmp.visible = a->visible;
	a->key = b->key;
	a->value = b->value;
	a->visible = b->visible;
	b->key = tmp.key;
	b->value = tmp.value;
	b->visible = tmp.visible;
}

int	sort_pass(t_env *list)
{
	t_env	*ptr;
	int		swapped;

	swapped = 0;
	ptr = list;
	while (ptr->next != NULL)
	{
		if (ft_strcmp(ptr->key, ptr->next->key) > 0)
		{
			swap_env_nodes(ptr, ptr->next);
			swapped = 1;
		}
		ptr = ptr->next;
	}
	return (swapped);
}

t_env	*dupe_env(t_env *env)
{
	t_env	*new_head;
	t_env	*curr;
	t_env	*new_node;

	new_head = NULL;
	curr = NULL;
	while (env)
	{
		new_node = create_env_variable(env->key, env->value);
		if (!new_node)
			return (NULL);
		new_node->visible = env->visible;
		if (!new_head)
		{
			new_head = new_node;
			curr = new_node;
		}
		else
		{
			curr->next = new_node;
			curr = new_node;
		}
		env = env->next;
	}
	return (new_head);
}
