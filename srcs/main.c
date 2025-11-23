/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 04:06:12 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/23 04:08:07 by avelandr         ###   ########.fr       */
=======
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
>>>>>>> 4e010f65a06e4435fcfc68b687145507eb73604f
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//int	g_status = 0;

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
<<<<<<< HEAD
	return (minishell(argc, argv, env));
}
=======
	t_shell	data;

	if (argc != 1 || argv[1] != NULL)
		return (1);
	init_shell(argc, argv, env, &data);
	loop(&data);
	return (0);
}

/*int main(int argc, char **argv, char **env)
{
	if (!init_shell(argc, argv, env))
		return (EXIT_FAILURE);
	loop();
    terminator();
	return (EXIT_SUCCESS);
}*/
>>>>>>> 4e010f65a06e4435fcfc68b687145507eb73604f
