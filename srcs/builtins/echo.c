/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 18:59:13 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/22 18:59:45 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

void	print_args(char **args, int start, int n_flag)
{
	while (args[start])
	{
		ft_putstr_fd(args[start], STDOUT_FILENO);
		if (args[start + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		start++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	bt_echo(char **args)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = FALSE;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = TRUE;
		i++;
	}
	print_args(args, i, n_flag);
}
