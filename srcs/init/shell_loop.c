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

static void	free_cmd(void *content)
{
	t_cmd_table	*node;

	node = (t_cmd_table *)content;
	if (!node)
		return ;
	if (node->args)
		ft_free_split(node->args);
	ft_free_cmd_list(node);
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
	ft_lstclear(&cmd_list, &free_cmd);
	return (exit_status);
}

void	loop(t_shell *data)
{
	data->user_input = get_user_input(data);
	while (data->user_input != NULL)
	{
		set_signals_handlers_exec();
		if (data->user_input[0] != '\0')
		{
			add_history(data->user_input);
			g_status = execute(data);
		}
		terminator(data, FALSE);
	}
}
