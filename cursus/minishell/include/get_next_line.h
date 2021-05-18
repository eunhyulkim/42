/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 22:41:06 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/12 23:38:23 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define TRUE 1
# define FALSE 0
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

typedef struct	s_buf
{
	int		idx;
	int		read_nb;
	char	buf[3];
	int		res;
}				t_buf;

/*
** get_next_line.c
*/

int				get_next_line(int fd, char **line, int ret_opt);

/*
** get_next_line_util.c
*/

char			*ft_strjoin_bfnl(char *s1, char *s2);
int				ft_strlen_bfnl(char *str);
int				add_newline_return(char **line);

#endif
