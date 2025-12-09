#include "../Includes/libft.h"

char	*ft_strdup(const char *string)
{
	char		*str;
	size_t		size;
	size_t		i;

	if (!string)
		return (NULL);
	size = ft_strlen(string);
	if (size == 0)
		return (NULL);
	str = (char *)ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = string[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
