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

#include "../../includes/minishell.h"

// cuando readline detecta ctrl-d devuelve NULL
static char	*get_user_input(t_shell *data)
{
	char	*prompt_str;
	char	*input;

	set_signals_interactive();
	prompt_str = prompt(data);
	input = readline(prompt_str);
	free(prompt_str);
	return (input);
}

static int	execute(t_shell *data)
{
	t_list	*cmd_list;
	int		exit_status;

	cmd_list = NULL;
	cmd_list = ft_parse(data->user_input, data);
	if (!cmd_list)
		return (g_status);
	exit_status = ft_exec_cmd_line(cmd_list, data);
	if (cmd_list)
		ft_lstclear(&cmd_list, &free_cmd);
	cmd_list = NULL;
	return (exit_status);
}

void	loop(t_shell *data)
{
	int	i;

	i = 0;
	while (i < 5) // DEBUG para poder salir mientra no funcione el built-in
	{
		data->user_input = get_user_input(data);
		set_signals_handlers_exec();
		if (data->user_input && data->user_input[0] != '\0')
		{
			add_history(data->user_input);
			if (ft_lexer(data->user_input) == TRUE)
				g_status = execute(data);
			else
				g_status = print_msg
					(NULL, "syntax error near unexpected token", 2);
		}
		terminator(data, FALSE);
		i++;
	}
}
