#include "minishell.h"

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
	if (line->hist && !line->hist_depth)
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
	if (line->hist && line->hist_depth == line->hist_size)
		return ;
	if (!line->hist_depth)
		ft_dlstadd(hist, ft_dlstnew(line->cmd, ft_strlen(line->cmd) + 1));
	*hist = (*hist)->next;
	line->hist_depth++;
	feed_line(line, (*hist)->content);
	ft_putstr_fd(line->cmd, 0);
}

void	match_hist(int key_pressed, t_line *line)
{
	int						i;
	static t_keyhist	keyhist[2] = {
		{KEY_UP, &old_hist_entry},
		{KEY_DOWN, &new_hist_entry}
	};

	i = 0;
	while (i < 2)
		if (key_pressed == keyhist[i++].key)
			keyhist[i - 1].p(line, &(line->hist));
}

void		append_history(char *entry)
{
	int		fd;

	if (!(*entry))
		return ;
	fd = open(HISTORY_PATH, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putendl_fd("Could not open history", 2);
		return ;
	}
	ft_putendl_fd(entry, fd);
	close(fd);
}

t_dlist		*retrieve_history(void)
{
	int		fd;
	t_dlist	*hist;
	char	*line;
	size_t	len;

	hist = NULL;
	fd = open(HISTORY_PATH, O_RDONLY | O_CREAT);
	if (fd == -1)
		return (NULL);
	while (get_next_line(fd, &line, FALSE))
	{
		len = ft_strlen(line);
		if (len < MAX_CMD_LEN)
			ft_dlstadd(&hist, ft_dlstnew(line, len + 1));
		free(line);
	}
	close(fd);
	return (hist);
}
