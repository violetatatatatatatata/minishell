#include "../Includes/libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	if (*to_find == '\0')
		return ((char *)str);
	while (str[i])
	{
		n = 0;
		while ((str[i + n] == to_find[n]) && ((i + n) < len))
		{
			if (str[i + n] == '\0')
				return ((char *)str + i);
			n++;
		}
		if (to_find[n] == '\0')
			return ((char *)str + i);
		i++;
	}
	return (0);
}
