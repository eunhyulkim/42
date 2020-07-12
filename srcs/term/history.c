#include "minishell.h"

static void	feed_line(t_line *line, char *entry)
{
	dprintf(g_fd, "enter feed_line functions...\n");
	cursor_to_home(line);
	dprintf(g_fd, "cursor_to_home function passed...\n");
	tputs(tgetstr("cd", NULL), 0, &tc_putc);
	dprintf(g_fd, "tputs passed\n");
	ft_bzero(line->cmd, MAX_CMD_LEN);
	ft_strcpy(line->cmd, entry);
	dprintf(g_fd, "ft_strcpy function passed...\n");
	line->cursor = ft_strlen(entry);
	line->length = line->cursor;
}

void		new_hist_entry(t_line *line, t_dlist **hist)
{
	dprintf(g_fd, "enter new_hist functions...\n");
	if (line->hist && !line->hist_depth)
		return ;
	line->hist_depth--;
	dprintf(g_fd, "hist address is [%p]\n", hist);
	dprintf(g_fd, "hist ponting address is [%p]\n", *hist);
	*hist = (*hist)->prev;
	dprintf(g_fd, "renewal hist address is [%p]\n", *hist);
	feed_line(line, (*hist)->content);
	dprintf(g_fd, "pass feed_line...\n");
	ft_putstr_fd(line->cmd, 0);
	dprintf(g_fd, "pass ft_putstr_fd...\n");
	if (!line->hist_depth)
		ft_dlstremovenode(hist);
	else
		dprintf(g_fd, "ft_dlstremovenode not executed...\n");
	dprintf(g_fd, "pass new_hist_entry function passed...\n");
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

	dprintf(g_fd, "enter match hist functions...\n");
	static struct s_keyhist	keyhist[2] = {
		{KEY_UP, &old_hist_entry},
		{KEY_DOWN, &new_hist_entry}
	};
	dprintf(g_fd, "keyhist[0][%d: %p]\n", keyhist[0].key, keyhist[0].p);
	dprintf(g_fd, "keyhist[1][%d: %p]\n", keyhist[1].key, keyhist[1].p);
	i = 0;
	while (i < 2)
	{
		if (key_pressed == keyhist[i++].key)
		{
			dprintf(g_fd, "run new_hist_entry with argument [%p]\n", &(line->hist));
			keyhist[i - 1].p(line, &(line->hist));
		}
	}
	dprintf(g_fd, "pass match_hist functions...\n");
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
	dprintf(g_fd, "retrieve_history fd is [%d]\n", fd);
		free(path);
	if (fd == -1)
		return (NULL);
	while (get_next_line(fd, &line, FALSE))
	{
		dprintf(g_fd, "line is [%s]\n", line);
		len = ft_strlen(line);
		if (len < MAX_CMD_LEN)
			ft_dlstadd(&hist, ft_dlstnew(line, len + 1));
		free(line);
	}
	close(fd);
	return (hist);
}
