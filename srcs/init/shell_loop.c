/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 01:11:43 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/23 01:12:33 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// cuando readline detecta ctrl-d devuelve NULL
void	loop(void)
{
	char	*prompt_str;

	while (1)
	{
		set_signals_interactive();
		prompt_str = prompt();
		data->user_input = readline(prompt_str);
		free(prompt_str);
		if (data->user_input == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			terminator(data, TRUE);
		}
		set_signals_handlers_exec();
		if (data->user_input && data->user_input[0] != '\0')
		{
			add_history(data->user_input);
			if (lexparsexpander(data) == TRUE)
				g_status = execute(data);
			else
				g_status = 1;
		}
		terminator(data, FALSE);
	}
}
