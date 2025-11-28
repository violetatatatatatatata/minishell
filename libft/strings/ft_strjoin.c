#include "../Includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*str;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)ft_calloc(size, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, size);
	ft_strlcat(str, s2, size);
	return (str);
}
