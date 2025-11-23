/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:00:11 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/22 19:05:06 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	change_dir(t_values *data, char *dir)
{
	char	*curpath;
	char	cwd[PATH_MAX];

	if (!chdir(dir))
		return (print_msg(("cd", DIR_FAILED, EXIT_FAILURE)));
	curpath = getcwd(cwd, PATH_MAX);
	if (!curpath)
		return (print_msg(("cd", DIR_FAILED, EXIT_FAILURE)));
	ft_setenv(data, "PATH", dir);
	return (EXIT_SUCESS);
}

int	bt_cd(char **args, t_values *data)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0]) || /
		args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
	{
		path = ft_getenv("HOME", data->env);
		if (!path || *path == '\0' || ft_isspace(*path))
			return (print_msg(("cd", HOME_FAILED, EXIT_FAILURE)));
		return (!chdir(data, path));
	}
	if (args[2])
		return (print_msg(("cd", DIR_FAILED, EXIT_FAILURE)));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = ft_getenv("OLDPWD", data->env);
		if (!path)
			return (print_msg("cd", "OLDPWD not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	return (change_dir(data, path));
}
