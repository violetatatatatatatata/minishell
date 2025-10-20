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

#include "minishell.h"

int	main(int count, char **args, char **env)
{
	t_values	values;
	char		*line;

	if (count != 1 || args[1] != NULL)
		return (1);
	values.env = env;
	while (1)
	{
		line = NULL;
		printf("stdin = %d, isatty(stdin)? %d\n", STDIN_FILENO, isatty(STDIN_FILENO));
		line = readline(">> ");
		add_history(line);
		values.tokens = ft_tokenize(line, &values.num_cmds, values.env);
		free(line);
		values.pids = malloc(sizeof(pid_t) * values.num_cmds);
		ft_parse(&values);
		printf("END PARSE\n");
		ft_free_vals(&values);
	}
	return (0);
}
