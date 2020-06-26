#include "minishell.h"

// static void		excute_line(t_line *line)
// {
// 	if (!excute_redirects(line))
// 		return ;
// 	excute_commands(line);
// }

int				main(int ac, char *av[], char **env)
{
	// char	**lines;
	// t_line	*line;

	(void)ac;
	(void)av;
	// init_shell();
	init_env(env);
	printf("RIGHT_KEY: %s\n", get_env("LANG"));
	printf("RIGHT_KEY: %s\n", get_env("SHELL"));
	printf("RIGHT_KEY: %s\n", get_env("PATH"));
	printf("SUB_KEY: %s\n", get_env("COLOR"));
	printf("FALSE_KEY: %s\n", get_env("ASDASF"));
	printf("NONE_VALUE_KEY: %s\n", get_env("_CE_M"));
	printf("EMPTY_KEY: %s\n", get_env(""));
	printf("NULL_KEY: %s\n", get_env(NULL));
	// while (TRUE)
	// {
		// prompt();
		// if (!(lines = readlines()))
		// 	continue;
		// while (*lines)
		// {
 		// 	line = parselines(*lines++);
		// 	excute_line(line);
		// }
	// }
	// free_double_err(g_env);
	return (0);
}
