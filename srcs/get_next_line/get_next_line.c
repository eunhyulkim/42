/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 22:41:27 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/07 00:29:55 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int	init_line(char **line)
{
	if (!(*line = malloc(sizeof(char))))
		return (-1);
	*line[0] = '\0';
	return (1);
}

int	init_buf_read(int fd, char *buf)
{
	int	read_nb;

	read_nb = 0;
	ft_memset(buf, '\0', 3);
	if (((read_nb = read(fd, buf, 2)) < 0))
		return (-1);
	return (read_nb);
}

int	read_if_buf_empty(int fd, t_buf *buf)
{
	if (buf->buf[0] == '\0')
		if ((buf->read_nb = init_buf_read(fd, buf->buf)) < 0)
			return (-1);
	return (1);
}

int	is_last_line_eof(int fd, t_buf *buf)
{
	if ((buf->read_nb = init_buf_read(fd, buf->buf)) < 0)
		return (-1);
	buf->idx = 0;
	if (buf->buf[0] == '\0')
		return (0);
	return (1);
}

int	add_newline_return(char **line)
{
	char *str;
	str = ft_strjoin(*line, "\n");
	free(*line);
	*line = str;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static t_buf	buf;

	if (fd < 0 || line == NULL)
		return (-1);
	if (init_line(line) < 0 || read_if_buf_empty(fd, &buf) < 0)
		return (-1);
	while (buf.read_nb != 0)
	{
		*line = ft_strjoin_bfnl(*line, &(buf.buf[buf.idx]));
		while (buf.buf[buf.idx] && buf.buf[buf.idx] != '\n')
			buf.idx++;
		if (buf.buf[buf.idx] == '\0')
		{
			if ((buf.res = is_last_line_eof(fd, &buf)) < 1)
				return (buf.res);
		}
		else
		{
			buf.idx++;
			return (add_newline_return(line));
		}
	}
	return (0);
}
