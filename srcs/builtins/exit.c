/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 exit.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/11/22 19:06:21 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/11/23 00:09:27 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <minishell.h>

static int	check_long_overflow(char *str)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_strlen(str) > ft_strlen(MAX_LONG)
			|| (ft_strlen(str) == ft_strlen(MAX_LONG)
				&& ft_strcmp(str, MAX_LONG) > 0))
			return (FALSE);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (TRUE);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (FALSE);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	bt_exit(t_shell *data, char **args)
{
	int	exit_code;

	// ft_putendl_fd("exit", STDERR_FILENO);
	if (!args[1])
	{
		exit_code = g_status;
		terminator(data, exit_code);
	}
	if (!check_long_overflow(args[1]) || !is_numeric(args[1]))
	{
		print_msg("exit", "numeric argument required", EXIT_FAILURE);
		terminator(data, 2);
	}
	if (args[2])
		print_msg("exit", "too many arguments", EXIT_FAILURE);
	// modificar atoi para que funcione con longs
	exit_code = ft_atoi(args[1]);
	terminator(data, exit_code);
	return (EXIT_SUCCESS);
}
