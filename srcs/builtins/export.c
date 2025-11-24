/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:58:49 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/24 16:37:32 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_valid_id(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (FALSE);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void	handle_export(t_shell *data, char *args)
{
	char	*key;
	char	*value;
	char	*pos;

	pos = ft_strchr(arg, '=');
	key = ft_getkey(arg, pos);
	value = ft_getvalue(arg, pos);
	ft_setenv(data, key, value);
	free(key);
	free(value);
}

int	print_sorted_env(t_env *env)
{
	int		i;
	int		size;

	size = count_env_vars(env);
	cpy_env = (t_env **)malloc(sizeof(t_env *) * (size + 1));
	if (!cpy_env)
		return (EXIT_FAILURE);
	cpy_env = dupe_env(env, size);
	i = -1;
	while (++i < size)
	{
		if (cpy_env[i]->visible)
		{
			printf("declare -x %s", cpy_env[i]->key);
			if (cpy_env[i]->value)
				printf("=\"%s\"", cpy_env[i]->value);
			printf("\n");
		}
	}
	free(cpy_env);
	return (EXIT_SUCCESS);
}

int	bt_export(t_shell *data, char **args)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = EXIT_SUCCESS;
	if (!args[1])
		return (print_sorted_env(data->env));
	while (args[i])
	{
		if (!is_valid_id(args[i]))
		{
			return (print_msg("export", "not a valid identifier", 1));
			exit_status = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], "=") != NULL)
			handle_export(data, args[i]);
		else
		{
			if (!ft_getenv(args[i], data->env))
				ft_setenv(data, args[i], NULL);
		}
		i++;
	}
	return (exit_status);
}
