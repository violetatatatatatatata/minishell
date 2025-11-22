/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:34:28 by aalcaide          #+#    #+#             */
/*   Updated: 2025/10/06 14:34:30 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief Tells the size of a char** until the NULL val
/// @param arr
/// @return Integer size of the array
int	ft_double_arr_size(char **arr)
{
	int	size;

	if (!arr)
		return (0);
	size = 0;
	while (arr[size])
		size++;
	return (size);
}

/// @brief Tells the size of a char*** until the NULL val
/// @param arr
/// @return Integer size of the array
int	ft_triple_arr_size(char ***arr)
{
	int	size;

	if (!arr)
		return (0);
	size = 0;
	while (arr[size])
		size++;
	return (size);
}

int	ft_count_arr(char ***tokens)
{
	int	i;
	int	arr_size;
	int	size;

	arr_size = ft_double_arr_size(*tokens);
	i = 0;
	size = 0;
	while (i < arr_size)
	{
		if (ft_strncmp((*tokens)[i], "<<", 3) == 0
			|| ft_strncmp((*tokens)[i], "<", 2) == 0)
		{
			i += 2;
			continue ;
		}
		i++;
		size++;
	}
	return (size);
}

char	**ft_dup_tokens(char **tokens)
{
	int		i;
	char	**dup;

	if (!tokens)
		return (NULL);
	i = 0;
	while (tokens[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		dup[i] = ft_strdup(tokens[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

int	ft_isvalid_envvar(char *name, t_shell data)
{
	char	*var;

	var = ft_getenv(name, data.env);
	if (!var)
		return (0);
	return (1);
}
