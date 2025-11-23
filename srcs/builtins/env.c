/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:05:46 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/22 19:06:07 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bt_env(t_shell *data, char **args)
{
	t_env	*tmp;

	if (args[1])
		return (print_msg("env", "too many args", 1));
	tmp = data->env;
	while (tmp)
	{
		if (tmp->value != NULL && tmp->visible)
			printf("%s = %s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
