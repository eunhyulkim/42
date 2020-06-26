#include "minishell.h"

// if key exist in env but value is not, return empty string pointer
// if key not in env, return null

char	*get_env(char *key)
{
	int		idx;

	if (!g_env || !key || !(*key))
		return (0);
	idx = 0;
	while (g_env[idx])
	{
		if (ft_startswith(g_env[idx], key))
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
