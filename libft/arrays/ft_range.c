#include "../Includes/libft.h"

int	*ft_range(int min, int max)
{
	int	*range;
	int	iter;

	iter = min;
	if (min >= max)
	{
		return (0);
	}
	range = (int *)malloc(sizeof(int) * (max - min));
	if (range == 0)
		return (0);
	while (iter < max)
	{
		range[iter - min] = iter;
		iter++;
	}
	return (range);
}
