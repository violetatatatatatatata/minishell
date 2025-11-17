/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//int	g_status = 0;

int	main(int count, char **args, char **env)
{
	//t_values	values;
	char	*line;
	t_list	*cmd_list;

	if (count != 1 || args[1] != NULL)
		return (1);
	//values.env = env;
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
		cmd_list = ft_parse(line, env);
		ft_exec_cmd_line(cmd_list, env);
		free(line);
	}
	return (0);
}

/*int main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)env;
	ft_memset(&data, 0, sizeof(t_data));
	if (!check_execution(&data, argc, argv))
	{
		print_msg(INPUT_ERROR, RED);
		return(EXIT_FAILURE);
	}
	//	exit_shelly();
	if (data.is_interactive)
		exect_interactive(&data);
	else
		exect_noninteractive(&data, argc, argv);//temporal
//	exit_shelly(&data);
	return (EXIT_SUCCESS);
}*/
