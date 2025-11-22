#include <minishell.h>

t_env   *create_env_variable(char *key, char *value)
{
	int		visible;
    t_env   *node;

	visible = TRUE;
    node = ft_calloc(1, sizeof(t_env));
    if (node)
	{
		if (value == NULL || value == "")
			visible = FALSE;
        create_node(node, ft_strdup(key), ft_strdup(value), visible);
	}
	return (node);
}

void ft_setenv(t_shell *data, char *key, char *value)
{
    t_env   *current;

    current = data->env;
    while (current->next != NULL)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return ;
        }
        current = actual->next;
    }
    if (current)
        current->next = create_env_variable(key, value);
    else
        data->env = create_env_variable(key, value);    // lista vacía
}

char    *ft_getenv(const char *key, t_env *env)
{
	while(env)
	{
		// ojo pelao con el export
		if(ft_strcmp(env->key) == 0 && env->visible)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
