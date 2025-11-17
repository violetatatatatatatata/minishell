int	bt_echo(char **args)
{
	int	is_n_flag;
	int	i;

	n_arg = 0;
	n_flag = is_n_flag(args);
	while (args[i] && )
	{
		while (i < ft_strlen(argv[num_arg]))
		{
			/*error en el write*/
			if (write(1, &argv[num_arg][i], 1) < 0)
				return (EXIT_FAILURE);
			i++;
		}
		if (print_newline && i == ft_strlen(argv[num_arg]))
			write(1, "\n", 1);
		num_arg++;
	}
	return (EXIT_SUCCESS);
}

int	is_n_flag
{

}

void	print_args(char **args, int n_flag, int i)
{
	if (!args[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
			return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		// i++;
	}
}
