#include <minishell.h>

void	bt_pwd(t_shell *data)
{
	char	*pwd;
	char	*cwd;

	pwd = ft_getenv("PWD", data->env);
	if (pwd)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
	}
	else
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			ft_putendl_fd(pwd, STDOUT_FILENO);
			free(cwd);
		}
	}
}
