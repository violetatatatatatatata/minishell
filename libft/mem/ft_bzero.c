#include "../Includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	while (0 < n--)
	{
		((unsigned char *)s)[n] = 0;
	}
}
