#include "minishell.h"

// if key exist in env but value is not, return empty string pointer
// if key not in env, return null

static	int		get_key_idx(char *key)
{
	int		idx;

	idx = 0;
	while (g_env[idx])
	{
		if (ft_startswith(g_env[idx], key))
			if (*(g_env[idx] + ft_strlen(key)) == '=')
				return (idx);
		idx++;
	}
	return (-1);
}

int		set_env(char *key, char *val)
{
	int		idx;
	char	*item;
	char	**new_env;

	if (!key || !(*key))
		return (0);
	idx = get_key_idx(key);
	if (idx != -1)
	{
		free(g_env[idx]);
		item = ft_strjoin(key, "=");
		g_env[idx] = ft_strjoin(item, val);
		free(item);
	}
	else
	{
		item = ft_strjoin(ft_strjoin(key, "="), val);
		new_env = ft_realloc_doublestr(g_env, item);
		ft_free_doublestr(g_env);
		g_env = new_env;
		free(item);
	}
	return (1);
}

char	*get_env(char *wild_key)
{
	int		idx;
	char	*key;

	if (!g_env || !wild_key || !(*wild_key))
		return (0);
	if ((key = ft_strchr(wild_key, '=')))
		key = ft_strsub(wild_key, 0, key - wild_key);
	else
		key = wild_key;
	if ((idx = get_key_idx(key)) == -1)
		return (0);
	return (g_env[idx] + ft_strlen(key) + 1);
}

void	init_env(char **env)
{
	g_env = (char **)ft_dup_doublestr(env);
}
