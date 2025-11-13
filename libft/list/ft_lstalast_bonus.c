#include "../Includes/libft.h"

t_list	*ft_lstalast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next && lst->next->next)
		lst = lst->next;
	return (lst);
}
