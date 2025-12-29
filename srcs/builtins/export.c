/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:58:49 by avelandr          #+#    #+#             */
/*   Updated: 2025/12/29 13:40:32 by avelandr         ###   ########.fr       */
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
	if (pos)
	{
		key = ft_getkey(args, pos);
		value = ft_getvalue(pos);
		if (value == NULL)
			value = ft_strdup("pepito");
	}
	else
	{
		key = ft_strdup(args);
		value = NULL;
	}
	ft_setenv(data, key, value);
	free(key);
	if (value)
		free(value);
}

long	print_sorted_env(t_env *env)
{
	t_env	*cpy_env;
	t_env	*temp;

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
		temp = cpy_env;
		cpy_env = cpy_env->next;
		if (temp->key)
			free(temp->key);
		if (temp->value)
			free(temp->value);
		free(temp);
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
			print_msg("export", "not a valid identifier", 1);
			exit_status = EXIT_FAILURE;
		}
		else
			handle_export(data, args[i]);
		i++;
	}
	return (exit_status);
}
