/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factorization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 03:09:34 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/02 19:48:25 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#define ERROR	0
#define SKIP	0
#define SUCCESS	1

/*
** On exception, program exit with an error message.
*/
void	leave(char *err_msg)
{
	int		len;

	len = 0;
	while (err_msg[len])
		len++;
	write(1, err_msg, len);
	write(1, "\n", 1);
	exit(1);
}

/*
** Argument is converted to an unsigned int.
** For exceptions occurring in the process,
** Program exit with an error message.
*/
unsigned int	ft_atoui(char *str)
{
	long long	nb;
	int		idx;

	if (!str || !(*str))
		leave("argument is not exists");
	nb = 0;
	idx = 0;
	if (str[idx] == '-')
		leave("factorization does not treat negative number");
	if (str[idx] == '+')
		idx++;
	while (str[idx] == '0')
		idx++;
	while (str[idx])
	{
		if (str[idx] < '0' || str[idx] > '9')
			leave("argument contains non-numeric character");
		nb = nb * 10 + (str[idx] - '0');
		if (nb > UINT_MAX)
			leave("argument exceeded the range of unsigned int");
		idx++;
	}
	return ((unsigned int)nb);
}

void	ft_putnbr(unsigned int nb)
{
	char	c;

	if (nb >= 10)
		ft_putnbr(nb / 10);
	c = (nb % 10) + '0';
	write(1, &c, 1);
}

/*
** If the given number proves to be prime,
** it ends without printing.
** Otherwise, it is printed starting from the smallest number.
*/
int	ft_factorization(unsigned int nb)
{
	unsigned int	i;
	unsigned int	origin;
	unsigned int	printed;

	i = 2;
	origin = nb;
	printed = 0;
	while (nb != 1)
	{
		if (origin == nb && origin / i < i)
			return (SKIP);
		if (nb % i == 0)
		{
			nb = nb / i;
			if (printed != i && printed != 0)
				write(1, " ", 1);
			if (printed != i)
				ft_putnbr(i);
			printed = i;
		}
		else
			i++;
	}
	write(1, "\n", 1);
	return (SUCCESS);
}

int	main(int ac, char *av[])
{
	unsigned int	nb;

	if (ac != 2)
		leave("argument count is invalid");
	nb = ft_atoui(av[1]);
	if (nb == 0 || nb == 1)
		leave("argument range is a number greater than 1");
	ft_factorization(nb);
	return (0);
}
