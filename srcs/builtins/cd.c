/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:00:11 by avelandr          #+#    #+#             */
/*   Updated: 2025/12/15 16:57:58 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	change_dir(t_values *data, char *dir)
{
	char	*old_pwd;
	char	cwd[PATH_MAX];

	old_pwd = ft_getenv("PWD", data->val_env->env);
	if (chdir(dir) == -1)
		return (print_msg("cd", DIR_FAILED, EXIT_FAILURE));
	if (old_pwd)
		ft_setenv(data->val_env, "OLDPWD", old_pwd);
	if (getcwd(cwd, PATH_MAX))
		ft_setenv(data->val_env, "PWD", cwd);
	else
		ft_setenv(data->val_env, "PWD", dir);
	return (EXIT_SUCCESS);
}

int	bt_cd(char **args, t_values *data)
{
	char	*path;

	path = NULL;
	if (!args || !args[1] || ft_isspace(args[1][0])
		|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
	{
		path = ft_getenv("HOME", data->val_env->env);
		if (!path || *path == '\0' || ft_isspace(*path))
			return (print_msg("cd", HOME_FAILED, EXIT_FAILURE));
		return (!chdir(path));
	}
	if (args[2])
		return (print_msg("cd", DIR_FAILED, EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = ft_getenv("OLDPWD", data->val_env->env);
		if (!path)
			return (print_msg("cd", "OLDPWD not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	return (change_dir(data, args[1]));
}
