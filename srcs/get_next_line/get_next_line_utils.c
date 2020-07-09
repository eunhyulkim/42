/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 23:51:17 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/09 18:42:44 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen_bfnl(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	return (len);
}

char	*ft_strjoin_bfnl(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*res;
	int		i;

	len1 = ft_strlen_bfnl(s1);
	len2 = ft_strlen_bfnl(s2);
	if (!(res = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	i = -1;
	while (++i < len1)
		res[i] = s1[i];
	res[i] = '\0';
	i = 0;
	while (i < len2)
	{
		res[len1 + i] = s2[i];
		i++;
	}
	res[len1 + i] = '\0';
	free(s1);
	return (res);
}

int		add_newline_return(char **line)
{
	char *str;

	str = ft_strjoin(*line, "\n");
	free(*line);
	*line = str;
	return (1);
}
