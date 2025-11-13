#include "../Includes/libft.h"

char	*ft_strdup(const char *s)
{
	char				*fin;
	unsigned long		tam;
	int					i;

	i = 0;
	tam = ft_strlen((char *)s);
	fin = (char *)malloc(sizeof(char) * tam + 1);
	if (!fin)
		return (NULL);
	while (s[i])
	{
		fin[i] = s[i];
		i++;
	}
	fin[i] = 0;
	return (fin);
}
