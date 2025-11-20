#include <minishell.h>

// un ft_lstsize pero pa t_env vamo
static int	count_env_vars(t_env *env)
{
	int	n_vars;

	n_vars = 0;
	while (env)
	{
		n_vars++;
		env = env->next;
	}
	return (n_vars);
}

static void	sort_env_array(t_env **list, int size)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(list[j]->key, list[j + 1]->key) > 0)
			{
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	dupe_env(t_env *env, t_env *cpy_env)
{
	int	i;

	i = 0;
	while (env)
	{
		cpy_env[i++] = env;
		env = env->next;
	}
	cpy_env[i] = NULL;
	sort_env_array(cpy_env, size);
}

int	print_sorted_env(t_env *env)
{
	int		i;
	int		size;
	t_env	**cpy_env;

	size = count_env_vars(env);
	cpy_env = (t_env **)malloc(sizeof(t_env *) * (size + 1));
	if (!cpy_env)
		return (EXIT_FAILURE);
	dupe_env(env, cpy_env)
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
