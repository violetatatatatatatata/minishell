/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 shell_loop.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/11/23 01:11:43 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/11/23 03:00:12 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <minishell.h>

// cuando readline detecta ctrl-d devuelve NULL
static char	*get_user_input(void)
{
	char	*prompt_str;
	char	*input;

	set_signals_interactive();
	prompt_str = prompt();
	input = readline(prompt_str);
	free(prompt_str);
	return (input);
}

static int	execute(t_shell *data)
{
	t_list	*cmd_list;
	int		exit_status;

	cmd_list = ft_parse(data->user_input, data);
	ft_exec_cmd_line(cmd_list, data);
	exit_status = // alguna funcion que indique el exit status
	return (exit_status);
}

void	loop(t_shell *data)
{
	data->user_input = get_user_input();
	while (data->user_input != NULL)
	{
		set_signals_handlers_exec();
		if (data->user_input[0] != '\0')
		{
			add_history(data->user_input);
			if (ft_lexer(line) == TRUE)
				g_status = execute(data);
			else
				g_status = 1;
		}
		terminator(data, FALSE);
	}
}

