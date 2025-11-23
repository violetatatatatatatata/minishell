#include "../Includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_lst)
{
	t_list	*tmp;

	if (!new_lst)
		return ;
	if (*lst == NULL)
		*lst = new_lst;
	else
	{
		tmp = ft_lstlast(*(lst));
		tmp->next = new_lst;
	}
}
