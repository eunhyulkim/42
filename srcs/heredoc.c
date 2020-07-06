#include "minishell.h"

char	*get_content(t_redir *redir)
{
	char 	*line;
	char 	*endstr;
	char 	*doc;
	char	*temp;

	endstr = ft_strjoin(redir->arg, "\n");
	line = 0;
	doc = ft_strdup("");
	write(1, "> ", 2);
	while (get_next_line(1, &line) > 0)
	{
		if (!ft_strcmp(line, endstr))
			break ;
		temp = ft_strjoin(doc, line);
		free(doc);
		doc = temp;
		write(1, "> ", 2);
	}
	free(endstr);
	return (doc);
}

void	convert_heredoc(t_redir *redir)
{
	char 	*heredoc;
	int		fd;

	heredoc = get_content(redir);
	if ((fd = open(TEMP_PATH, O_RDWR | O_CREAT | O_TRUNC, 0644) < 0))
		return ;
	write(fd, heredoc, ft_strlen(heredoc));
	close(fd);
	return ;
}