#include "minishell.h"

// void	init_env(char **env)
// {
// 	int		i;
// 	char	*mid;

// 	i = 0;
// 	while (env[i])
// 	{
// 		mid = ft_strchr(env[i], '=');
// 		g_env[i][0] = ;
// 		g_env[i][1] = ;
// 		i++;
// 	}
// }

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
	free_double_err(g_env);
	return (0);
}
