#include "libft.h"
#include <stdio.h>

int main(void)
{
	char	**str;
	int		idx;

	idx = 0;
	str = ft_split("HELLO;asd", ';');
	while (str[idx])
	{
		printf("[%s]", str[idx]);
		idx++;
	}
	printf("\n");
	return (0);
}