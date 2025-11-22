#include <minishell.h>

static int	check_long_overflow(char *str)
{
	unsigned long long	res;
	int					i;

	res = 0;
	i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
	while (str[i])
	{
		if (res > LLONG_MAX /*|| (res == LLONG_MAX && (str[i] - '0') > 7)*/)
			return (FALSE);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (TRUE);
}

int	is_numeric(char *str)
{
    int i = 0;

    if (str[i] == '-' || str[i] == '+')
		i++;
    if (!str[i])
		return (FALSE);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
			return (FALSE);
        i++;
    }
    return (TRUE);
}

static void	exit_shell(t_shell *data, int code)
{
	terminator(data, code);
	// exit(code);
}

int	bt_exit(t_shell *data, char **args)
{
	int	exit_code;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!args[1])
	{
		exit_code = g_status;
		exit_shell(data, exit_code);
	}
	if (!check_long_overflow(args[1]) || !is_numeric(args[1]))
	{
		print_msg("exit", "numeric argument required", 0);
		exit_shell(data, exit_code);
	}
	// aqui NO SALE DE LA SHELL
	if (args[2])
	{
		print_msg("exit", "too many arguments", 0);
		return (EXIT_FAILURE);
	}
	exit_code = ft_atoi(args[1]);
	exit_shell(data, exit_code);
	return (EXIT_SUCCESS);
}
