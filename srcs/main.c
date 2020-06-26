#include "minishell.h"

static void		excute_line(t_line *line)
{
	if (!excute_redirects(line))
		return ;
	excute_commands(line);
}

int				main(int ac, char *av[], char **env)
{
	char	**lines;
	t_line	*line;

	(void)ac;
	(void)av;
	init_shell();
	init_env(env);
	while (TRUE)
	{
		prompt();
		if (!(lines = readlines()))
			continue;
		while (*lines)
		{
 			line = parselines(*lines++);
			excute_line(line);
		}
	}
	ft_free_doublestr(g_env);
	return (0);
}
