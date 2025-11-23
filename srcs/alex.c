void	loop(t_shell *data)
{
	char	*line;
	t_list	*cmd_list;

	while (1)
	{
		line = NULL;
		printf("stdin = %d, isatty(stdin)? %d\n",
			STDIN_FILENO, isatty(STDIN_FILENO));
		line = readline(">> ");
		add_history(line);
		if (ft_lexer(line) == FALSE)
		{
			printf("LEXER ERROR\n");
			continue ;
		}
		cmd_list = ft_parse(line, data);
		ft_exec_cmd_line(cmd_list, data);
		free(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	data;

	if (argc != 1 || argv[1] != NULL)
		return (1);
	init_shell(argc, argv, env, &data);
	loop(&data);
	return (0);
}
