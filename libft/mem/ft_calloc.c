#include "../Includes/libft.h"

void	*ft_calloc(unsigned long nelem, unsigned long elsize)
{
	void	*ptr;

	if ((nelem * elsize) > 2147483647)
		return (NULL);
	ptr = (void *)malloc(nelem * elsize);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nelem * elsize);
	return (ptr);
}
