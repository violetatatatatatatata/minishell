int	bt_echo(char **args, int print_newline)
{
	int	i;
	int	num_arg;

	i = 0;
	num_arg = 1;
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
