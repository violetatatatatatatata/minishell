/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_command_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/12/17 19:12:16 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_free_memory(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

/*
** solo busca la ruta válida.
** retorna la ruta allocada si la encuentra, o NULL si no.
*/
static char	*find_correct_path(char **paths, char *cmd_name)
{
	char	*correct_path;
	char	*dir_with_slash;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		dir_with_slash = ft_strjoin(paths[i], "/");
		correct_path = ft_strjoin(dir_with_slash, cmd_name);
		free(dir_with_slash);
		if (access(correct_path, F_OK) == 0 && access(correct_path, X_OK) == 0)
			return (correct_path);
		free(correct_path);
		i++;
	}
	return (NULL);
}

char	*ft_find_command_path(char *cmd, t_shell *data)
{
	char	**paths;
	char	**prefixes;
	char	*env_path;
	char	*final_path;

	env_path = ft_getenv("PATH", data->env);
	if (env_path == NULL)
		return (ft_strdup(cmd));
	paths = ft_split(env_path, ':');
	prefixes = ft_split(cmd, ' ');
	final_path = find_correct_path(paths, prefixes[0]);
	ft_free_memory(paths);
	ft_free_memory(prefixes);
	if (final_path)
		return (final_path);
	return (ft_strdup(cmd));
}
