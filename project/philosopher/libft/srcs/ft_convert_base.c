/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:59:19 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/08 01:56:13 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					is_error(char *base, char *new_base)
{
	int				i;
	int				j;

	if (base[0] == '\0')
		return (1);
	i = -1;
	while (base[++i])
	{
		if (base[i] == '+' || base[i] == '-' || base[i] == ' ' ||
			(base[i] >= 9 && base[i] <= 13))
			return (1);
		j = i;
		while (base[++j])
		{
			if (base[i] == base[j])
				return (1);
		}
		new_base[(int)base[i]] = i;
		new_base[256] += 1;
	}
	if (new_base[256] < 2)
		return (1);
	return (0);
}

int					ft_convert_from(char *str, char *base)
{
	int				i;
	t_llint			v;
	int				sign;

	i = 0;
	sign = 1;
	v = 0;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\n' ||
			str[i] == '\r' || str[i] == ' ' || str[i] == '\f')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (base[(int)str[i]] != -1)
	{
		v *= (t_llint)base[256];
		v += (t_llint)base[(int)str[i]];
		i++;
	}
	return ((int)(v * sign));
}

char				*ft_convert_to(int rbr, char *base, char *nt_base)
{
	char			*result_s;
	int				i;
	t_llint			r_arr[2];
	t_llint			nbr;

	r_arr[1] = (rbr < 0) ? -1 : 1;
	r_arr[0] = (rbr < 0) ? ((t_llint)rbr * (-1)) : (t_llint)rbr;
	i = (rbr <= 0) ? 1 : 0;
	nbr = r_arr[0];
	while (nbr > 0)
	{
		i++;
		nbr = nbr / (t_llint)nt_base[256];
	}
	result_s = malloc(sizeof(char) * (i + 1));
	result_s[i--] = '\0';
	while ((r_arr[1] == 1 && i >= 0) || (r_arr[1] == -1 && i > 0))
	{
		result_s[i--] = base[(int)(r_arr[0] % (t_llint)nt_base[256])];
		r_arr[0] = r_arr[0] / (t_llint)nt_base[256];
	}
	if (r_arr[1] == -1)
		result_s[0] = '-';
	return (result_s);
}

char				*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int				result_i;
	char			*result_s;
	char			nf_base[257];
	char			nt_base[257];
	int				i;

	i = 0;
	result_s = 0;
	result_i = 0;
	while (i < 257)
	{
		nf_base[i] = -1;
		nt_base[i] = -1;
		i++;
	}
	nf_base[256] = 0;
	nt_base[256] = 0;
	i = 0;
	if (is_error(base_from, nf_base) || is_error(base_to, nt_base) ||
		!base_from || !base_to || !nbr)
		return (0);
	result_i = ft_convert_from(nbr, nf_base);
	result_s = ft_convert_to(result_i, base_to, nt_base);
	return (result_s);
}
