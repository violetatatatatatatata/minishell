/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 01:15:44 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/23 01:15:46 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// un ft_lstsize pero pa t_env vamo
static int	count_env_vars(t_env *env)
{
	int	n_vars;

	n_vars = 0;
	while (env)
	{
		n_vars++;
		env = env->next;
	}
	return (n_vars);
}

static void	sort_env_array(t_env *list, int size)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(list[j]->key, list[j + 1]->key) > 0)
			{
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

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

static int	sort_pass(t_env *list, t_env *last)
{
	t_env	*ptr;
	int		swapped;

	swapped = 0;
	ptr = list;
	while (ptr->next != last)
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

static void	dupe_env(t_env *env, t_env *cpy_env, int size)
{
	int	i;

	i = 0;
	while (env && i < size)
	{
		cpy_env = env;
		env = env->next;
		i++;
	}
	cpy_env = NULL;
	sort_env_array(cpy_env, size);
}

int	print_sorted_env(t_env *env)
{
	int		i;
	int		size;
	t_env	**cpy_env;

	size = count_env_vars(env);
	cpy_env = (t_env **)malloc(sizeof(t_env *) * (size + 1));
	if (!cpy_env)
		return (EXIT_FAILURE);
	dupe_env(env, cpy_env, size)
	i = -1;
	while (++i < size)
	{
		if (cpy_env[i]->visible)
		{
			printf("declare -x %s", cpy_env[i]->key);
			if (cpy_env[i]->value)
				printf("=\"%s\"", cpy_env[i]->value);
			printf("\n");
		}
	}
	free(cpy_env);
	return (EXIT_SUCCESS);
}
