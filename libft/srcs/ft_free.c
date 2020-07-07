#include "libft.h"

int		ft_free(char *str)
{
	if (str)
		free(str);
	return (1);
}
