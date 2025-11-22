#include <minishell.h>

// tema doble frees
void    free_node(t_env *node)
{
    if (!node)
        return ;
    if (node->key)
        free(node->key);
    if (node->value)
        free(node->value);
    free(node);
}

void    create_node(t_env *node, char *key, char *value, int state)
{
    node->key = key;
    node->value = value;
    node->visible = state;
    node->next = NULL;
}

void	ft_lstclear_env(t_env **lst)
{
	t_env	*current;
	t_env	*tmp;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		tmp = current->next;
		free_node(current);
		current = tmp;
	}
	*lst = NULL;
}

char	*ft_getkey(char *line, char *eq_pos)
{
    return (ft_substr(line, 0, (eq_pos - line)));
}

char	*ft_getvalue(char *eq_pos)
{
	return(ft_strdup(eq_pos + 1));
}
