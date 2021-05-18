/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 22:28:21 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/14 20:16:37 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	match_key(char *key_str, int i)
{
	static t_keymatch	key_couple[11] = {
		{KEY_CODE_UP, KEY_UP}, {KEY_CODE_DO, KEY_DOWN}, \
		{KEY_CODE_RI, KEY_RIGHT}, {KEY_CODE_LE, KEY_LEFT}, \
		{KEY_CODE_DEL, KEY_DC}, {KEY_CODE_HOME, KEY_HOME}, \
		{KEY_CODE_END, KEY_END}, {KEY_CODE_SRI, KEY_SRIGHT}, \
		{KEY_CODE_SLE, KEY_SLEFT}, {KEY_CODE_SUP, KEY_SPREVIOUS}, \
		{KEY_CODE_SDO, KEY_SNEXT}
	};

	i = 0;
	while (i < 11)
	{
		if (!ft_memcmp(key_couple[i].key_code, \
		key_str, MAX_KEY_LEN))
			return (key_couple[i].key_ret);
		i++;
	}
	return (key_str[0] == '\x5e' ? 0 : key_str[0]);
}

int			get_key(void)
{
	char	*key_str;
	int		key_pressed;

	if (!(key_str = ft_calloc(sizeof(char), 5)))
		return (-1);
	if (!key_str)
		return (-1);
	read(0, key_str, 1);
	if (*key_str == '\x1b')
		read(0, key_str + 1, 3);
	key_pressed = match_key(key_str, 0);
	ft_free_str(&key_str);
	return (key_pressed);
}
