/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 export.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/11/25 15:57:08 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/11/25 15:57:08 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <minishell.h>

static int	is_valid_id(char *str)
{
	int	i;

	i = 0;
	if (!str[i] || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (EXIT_FAILURE);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	export_var(t_shell *data, char *arg)
{
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	if (eq_pos)
	{
		*eq_pos = '\0';
		ft_setenv(data, arg, eq_pos + 1);
		*eq_pos = '=';
	}
	else
	{
		if (!ft_getenv(arg, data->env))
			ft_setenv(data, arg, NULL);
	}
}

int	bt_export(t_shell *data, char **args)
{
	int	i;
	int	ret;

	ret = EXIT_SUCCESS;
	if (!args[1])
		return (print_sorted_env(data->env));
	i = 1;
	while (args[i])
	{
		if (!is_valid_id(args[i]))
		{
			printf("export %s not a valid identifier", args[i]);
			ret = 1;
		}
		else
			export_var(data, args[i]);
		i++;
	}
	return (ret);
}
