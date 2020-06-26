#include "minishell.h"

char	*get_env(char *key)
{
	int		idx;

	if (!g_env || !key || !(*key))
		return (0);
	idx = 0;
	while (g_env[idx])
	{
		if (ft_strnstr(g_env[idx], key, ft_strlen(g_env[idx])))
			if (*(g_env[idx] + ft_strlen(key)) == '=')
				return (g_env[idx] + ft_strlen(key) + 1);
		idx++;
	}
	return (0);
}

void	init_env(char **env)
{
	g_env = (char **)ft_dup_doublestr(env);
}
