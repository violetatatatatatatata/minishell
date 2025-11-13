#include <minishell.h>

void	init_shell(int argc, char **argv, char **env)
{
	t_values	data;

	ft_memset(&data, 0, sizeof(data));
	print_prompt();
	shell->pid = getpid();
	shell->env = env_init(env);
	return (args_checker(argc, argv));
}

int	args_checker(int argc, char **argv)
{
	if (argc != 1 && argc != 3)
		return (print_msg(NULL, "args error", EXIT_FAILURE));
	if (argc == 3)
	{
		data->interactive = FALSE;
		if (!argv[1] || (argv[1] && ft_strcmp(argv[1], "-c") != 0))
			return (print_msg(NULL, "args error", EXIT_FAILURE));
		else if (!argv[2] || (argv[2] && argv[2][0] == '\0'))
			return (print_msg(NULL, "args error", EXIT_FAILURE));
	}
	else
		data->interactive = TRUE;
	return (EXIT_SUCCESS);
}

/* incluso si envp es NULL o está vacío, deberia poder inicializar
 * un entorno mínimo (PATH, PWD, SHLVL).
 * */
void	env_init(char **env)
{
	if (env)
		data->env = env;
	else
		handle_missing_env(data);
	// manejar la lista de la env
}
