/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrange.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 01:18:51 by eunhkim           #+#    #+#             */
/*   Updated: 2020/09/24 16:10:42 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		arrange(t_tab *tab)
{
	reinitialize(tab);
	check_flag(tab);
	check_width(tab);
	check_sharp(tab);
	check_size(tab);
	if (!check_type(tab))
		return (0);
	deliver(tab);
	if (tab->content)
		print_content(tab);
	return (1);
}
