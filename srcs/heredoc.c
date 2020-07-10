/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 02:14:07 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/10 09:28:23 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_content(t_redir *redir)
{
	char	*line;
	char	*endstr;
	char	*doc;

	endstr = ft_strjoin(redir->arg, "\n");
	line = 0;
	doc = ft_strdup("");
	write(1, "> ", 2);
	while (get_next_line(0, &line) > 0)
	{
		if (!ft_strcmp(line, endstr))
			break ;
		doc = ft_mstrjoin(doc, line);
		line = 0;
		write(1, "> ", 2);
	}
	ft_free(endstr);
	return (doc);
}

void	convert_heredoc(t_redir *redir)
{
	char	*heredoc;
	int		fd;

	heredoc = get_content(redir);
	if ((fd = open(TEMP_PATH, O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
		return ;
	write(fd, heredoc, ft_strlen(heredoc));
	close(fd);
	return ;
}
