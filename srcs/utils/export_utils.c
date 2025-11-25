/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 export_utils.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/11/25 16:00:20 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/11/25 16:00:20 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <minishell.h>

static int	count_vars(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static void	sort_tab(t_env **tab, int size)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(tab[j]->key, tab[j + 1]->key) > 0)
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static t_env	**list_to_array(t_env *env, int size)
{
	t_env	**tab;
	int		i;

	tab = malloc(sizeof(t_env *) * (size + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (env && i < size)
	{
		tab[i] = env;
		env = env->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	print_sorted_env(t_env *env)
{
	t_env	**tab;
	int		size;
	int		i;

	size = count_vars(env);
	tab = list_to_array(env, size);
	if (!tab)
		return (EXIT_FAILURE);
	sort_tab(tab, size);
	i = 0;
	while (i < size)
	{
		if (tab[i]->visible)
		{
			printf("declare -x %s", tab[i]->key);
			if (tab[i]->value)
				printf("=\"%s\"", tab[i]->value);
			printf("\n");
		}
		i++;
	}
	free(tab);
	return (EXIT_SUCCESS);
}
