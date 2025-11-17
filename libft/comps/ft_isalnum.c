#include "../Includes/libft.h"

int	ft_isalnum(int c)
{
	if ((c < 65 || c > 122 || (c < 97 && c > 90)) && (c < 48 || c > 57))
	{
		return (0);
	}
	return (1);
}
