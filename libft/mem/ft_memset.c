#include "../Includes/libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	size_t	iter;

	iter = 0;
	while (iter < count)
	{
		((char *)dest)[iter] = (char)c;
		iter++;
	}
	return (dest);
}
