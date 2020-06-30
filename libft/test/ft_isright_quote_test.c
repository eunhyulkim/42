#include "libft.h"
#include <stdio.h>

int main(void)
{
	printf("%d\n", ft_isright_quote("sad'as'd"));
	printf("%d\n", ft_isright_quote("s""ad'as'd"));
	printf("%d\n", ft_isright_quote("sad'a\"s'd"));
	printf("%d\n", ft_isright_quote("\"sadasd"));
	printf("%d\n", ft_isright_quote("sadasd\""));
	return (0);
}