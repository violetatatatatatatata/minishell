#include "../Includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t c)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < c)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
