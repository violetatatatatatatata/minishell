/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parse(t_values *values)
{
	int		i;

	i = 0;
	while (values->tokens[i])
	{
		ft_expand_dolar(&values->tokens, i, values->env);
		i++;
	}
	ft_exec_cmd_line(values);
	i = 0;
	while (values->tokens[i])
	{
		printf("Token final: %s of %i\n", values->tokens[i], i);
		i++;
	}
}
