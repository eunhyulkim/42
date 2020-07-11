/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 02:14:07 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/11 23:45:19 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_content(t_redir *redir)
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
	ft_free_str(&line);
	ft_free_str(&endstr);
	return (doc);
}

char		*get_config_path(char *filepath)
{
	return (ft_strsjoin(get_env("TEMP_ROOT"), "/", filepath, 0));
}

void		convert_heredoc(t_redir *redir)
{
	char	*heredoc;
	char	*temp_path;
	int		fd;

	heredoc = get_content(redir);
	temp_path = get_config_path(TEMP_PATH);
	if ((fd = open(temp_path, O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
		return ;
	write(fd, heredoc, ft_strlen(heredoc));
	ft_free_str(&heredoc);
	ft_free_str(&temp_path);
	close(fd);
	return ;
}
