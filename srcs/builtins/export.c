#include <minishell.h>

static int	is_valid_id(char *str)
{
	int	i;

	i = 0;
	// al menos el primer caracter es una letra o _
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (FALSE);
	i++;
	while (str[i] && str[i] != '=')
	{
		// que sean caracter
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
	char	pos;

	pos = ft_strchr(arg, '=');
	key = ft_getkey(arg, pos);
	value = ft_getvalue(arg, pos);
	if ()
	ft_setenv(data, key, val);
	free(key);
	free(value);
}

int	bt_export(t_shell *data, char **args)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = TRUE;
	if (!args[1])
		return (print_sorted_list(data->env));
	while (args[i])
	{
		if (!is_valid_id(args[i]))
		{
			return (print_msg("export", "not a valid identifier", 1));
			exit_status = FALSE;
		}
		else if (ft_strchr(args[i], "=") == 0)
			handle_export(data, args[i]);
		else
			if (!ft_getenv(args[i], data->env))
				ft_setenv(data, args[i], NULL);
		i++;
	}
	return (exit_status);
}
