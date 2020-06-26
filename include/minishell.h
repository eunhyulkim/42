#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

# define TRUE	 1
# define FALSE	 0

char	**g_env;

void	init_env(char **env);
char	*get_env(char *key);

# endif
