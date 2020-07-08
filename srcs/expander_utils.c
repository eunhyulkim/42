#include "minishell.h"

static int		has_wild(char *str)
{
	if (!ft_strchr(str, '*'))
		return (0);
	if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		return (0);
	return (1);
}

char			**get_paths(char *mask)
{
	char			**paths;
    struct dirent	*item;
    DIR				*dp;

	if (!has_wild(mask))
		return (0);
    if (!(dp = opendir(get_env("PWD"))))
		return (0);
	item = readdir(dp);
	paths = 0;
	while (TRUE)
	{
		if (!(item = readdir(dp)))
			break ;
		if (*item->d_name != '.' && ft_isformat2(item->d_name, mask))
			ft_realloc_doublestr(&paths, item->d_name);
	}
	closedir(dp);
	return (paths);
}
