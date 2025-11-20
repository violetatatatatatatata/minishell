#include <minishell.h>

// imprimir la fokin env
int	bt_env(t_shell *data, char **args)
{
	t_env	*tmp;

	// no se aceptan args en el subject
	if(args[1])
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
