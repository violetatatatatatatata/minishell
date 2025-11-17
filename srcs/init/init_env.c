#include <minishell.h>

static void	free_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

static void	*create_node(t_env node, char *key, char *value, int state)
{
	node->key = key;
	node->value = value;
	node->visible = state;
}

static t_env	*env_nodes(char *line)
{
	t_env	*new_node;
	char	*separator;
	char	*key;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	separator = ft_strchr(line, '=');
	if (!separator)
		create_node(new_node, ft_strdup(line), NULL, 0);
	else
	{
		key = ft_substr(line, 0, (ft_strlen(line) - ft_strlen(separator)));
		new_node = create_node(new_node, key, ft_strdup(separator + 1), 1);
	}
	new_node->next = NULL;
	if (!new_node->key || (separator != NULL && new_node->value))
	{
		free_node(new_node);
		return (NULL);
	}
	return (new_node);
}

t_env	*init_env(char **env)
{
	int		i;
	t_env	*head;
	t_env	*current;
	t_env	*new_node;

	i = -1;
	head = NULL;
	current = NULL;
	while (env[++i])
	{
		new_node = env_nodes(env[i]);
		if (!new_node)
			return (NULL);
		if (head == NULL)
		{
			head = new_node;
			current = head;
		}
		else
		{
			current->next = new_node;
			current = new_node;
		}
	}
	return (head);
}

void	handle_missing_env(data)
{

}
