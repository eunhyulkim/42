#include "libft.h"

int		ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (1);
}
