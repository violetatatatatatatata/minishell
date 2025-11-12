/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_command_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/06/02 10:55:31 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_free_memory(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*ft_find_command_path(const char *cmd, char **env)
{
	char	**paths;
	char	**prefixes;
	char	*ind_path;
	char	*correct_path;
	int		i;

	i = 0;
	paths = ft_split(ft_getenv("PATH", env), ':');
	prefixes = ft_split(cmd, ' ');
	while (paths[i])
	{
		ind_path = ft_strjoin(paths[i], "/");
		correct_path = ft_strjoin(ind_path, prefixes[0]);
		free(ind_path);
		if (access(correct_path, F_OK) == 0
			&& access(correct_path, X_OK) == 0)
			return (ft_free_memory(paths),
				ft_free_memory(prefixes), correct_path);
		free(correct_path);
		i++;
	}
	ft_free_memory(paths);
	ft_free_memory(prefixes);
	return (ft_strdup(cmd));
}
