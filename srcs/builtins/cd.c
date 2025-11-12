#include <minishell.h>

int bt_cd(char **args, t_values *data)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0]) \
			|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)	
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
	return (!change_dir(data, path));
}

static int	change_dir(t_values *data, char *dir)
{
	char	*curpath;
	char	cwd[PATH_MAX];

	if (!chdir(dir))
		return (print_msg(("cd", DIR_FAILED, EXIT_FAILURE)));
	curpath = getcwd(cwd, PATH_MAX);
	if (!curpath)
		return (print_msg(("cd", DIR_FAILED, EXIT_FAILURE)));
	update_env();
	return (EXIT_SUCESS);
}

void	update_env()
{
	ft_setenv()
}

/*
	current = getcwd(NULL, 0);
	if (current == NULL)
		return (print_msg(("cd", DIR_FAILED, EXIT_FAILURE)));
	env_home = get_env(env, "HOME");
*/
