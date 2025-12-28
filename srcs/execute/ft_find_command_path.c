/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_command_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/12/19 16:03:11 by avelandr         ###   ########.fr       */
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
	char	*env_path;
	char	*final_path;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	env_path = ft_getenv("PATH", data->env);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	final_path = find_correct_path(paths, cmd);
	ft_free_memory(paths);
	return (final_path);
}
