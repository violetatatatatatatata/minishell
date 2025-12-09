/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:58:49 by avelandr          #+#    #+#             */
/*   Updated: 2025/12/09 18:08:56 by avelandr         ###   ########.fr       */
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

	pos = ft_strchr(args, '=');
	key = ft_getkey(args, pos);
	value = ft_getvalue(pos);
	printf("key == %s\nvalue == %s\n", key, value);
	ft_setenv(data, key, value);
	free(key);
	free(value);
}

// HAY que hacer los frees del cpy_env y del contenido !!!!!!!!!!!
long	print_sorted_env(t_env *env)
{
	t_env	*cpy_env;

	cpy_env = dupe_env(env);
	sort_pass(cpy_env);
	while (cpy_env)
	{
		if (cpy_env->visible)
		{
			printf("declare -x %s", cpy_env->key);
			if (cpy_env->value != NULL)
				printf("=\"%s\"", cpy_env->value);
			printf("\n");
		}
		cpy_env = cpy_env->next;
	}
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
		else if (ft_strchr(args[i], '=') != NULL)
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
