/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 22:30:15 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/14 19:07:04 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	feed_line(t_line *line, char *entry)
{
	cursor_to_home(line);
	tputs(tgetstr("cd", NULL), 0, &tc_putc);
	ft_bzero(line->cmd, MAX_CMD_LEN);
	ft_strcpy(line->cmd, entry);
	line->cursor = ft_strlen(entry);
	line->length = line->cursor;
}

void		new_hist_entry(t_line *line, t_dlist **hist)
{
	if (!line->hist || !line->hist_depth)
		return ;
	line->hist_depth--;
	*hist = (*hist)->prev;
	feed_line(line, (*hist)->content);
	ft_putstr_fd(line->cmd, 0);
	if (!line->hist_depth)
		ft_dlstremovenode(hist);
}

void		old_hist_entry(t_line *line, t_dlist **hist)
{
	if (!line->hist || line->hist_depth == line->hist_size)
		return ;
	if (!line->hist_depth)
		ft_dlstadd(hist, ft_dlstnew(line->cmd, ft_strlen(line->cmd) + 1));
	*hist = (*hist)->next;
	line->hist_depth++;
	feed_line(line, (*hist)->content);
	ft_putstr_fd(line->cmd, 0);
}

void		append_history(char *entry)
{
	int		fd;
	char	*path;

	if (!(*entry))
		return ;
	path = get_config_path(HISTORY_PATH);
	fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		free(path);
		ft_putendl_fd("Could not open history", 2);
		return ;
	}
	free(path);
	ft_putendl_fd(entry, fd);
	close(fd);
}

t_dlist		*retrieve_history(void)
{
	int		fd;
	t_dlist	*hist;
	char	*line;
	size_t	len;
	char	*path;

	hist = NULL;
	path = get_config_path(HISTORY_PATH);
	fd = open(path, O_RDONLY | O_CREAT, 0644);
	free(path);
	if (fd == -1)
		return (NULL);
	line = 0;
	while (get_next_line(fd, &line, FALSE))
	{
		len = ft_strlen(line);
		if (len < MAX_CMD_LEN)
			ft_dlstadd(&hist, ft_dlstnew(line, len + 1));
		ft_free_str(&line);
	}
	ft_free_str(&line);
	close(fd);
	return (hist);
}
