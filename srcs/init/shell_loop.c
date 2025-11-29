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
/*
static void	free_tokens(t_token *token)
{
	if (!token)
		return ;
	if (token->content)
		free(token->content);
	if (token->left_side)
		free_tokens(token->left_side);
	if (token->right_side)
		free_tokens(token->right_side);
	free(token);
}
*/
/*
void	free_cmd(void *content)
{
	t_cmd_table	*node;

	node = (t_cmd_table *)content;
	if (!node)
		return ;
	if (node->args)
		ft_free_split(node->args);
	if (node->token)
		free_tokens(node->token);
	free(node);
}
*/
static int	execute(t_shell *data)
{
	t_list	*cmd_list;
	int		exit_status;

	cmd_list = ft_parse(data->user_input, data);
	if (!cmd_list)
		return (g_status);
	exit_status = ft_exec_cmd_line(cmd_list, data);
	ft_lstclear(&cmd_list, &free_cmd);
	return (exit_status);
}

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

void	loop(t_shell *data)
{
	int	i;

	i = 0;
	while (data->user_input != NULL) // DEBUG para poder salir mientra no funcione el built-in
	{
		data->user_input = get_user_input(data);
		set_signals_handlers_exec();
		if (data->user_input != NULL)
		{
			add_history(data->user_input);
			g_status = execute(data);
		}
		terminator(data, FALSE);
		i++;
	}
}
