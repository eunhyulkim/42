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

	if (!key || !(*key))
		return (0);
	idx = get_key_idx(key);
	key = ft_strjoin(key, "=");
	item = ft_strjoin(key, val);
	free(key);
	if (idx != -1)
	{
		free(g_env[idx]);
		g_env[idx] = item;
	}
	else
	{
		ft_realloc_doublestr(&g_env, item);
		free(item);
	}
	return (1);
}

char	*get_env(char *wild_key)
{
	int		key_idx;
	int		val_idx;
	char	*key;

	if (!g_env || !wild_key || !(*wild_key))
		return (0);
	if ((key = ft_strchr(wild_key, '=')))
		key = ft_strsub(wild_key, 0, key - wild_key);
	else
		key = ft_strdup(wild_key);
	if ((key_idx = get_key_idx(key)) == -1)
	{
		free(key);
		return (0);
	}
	val_idx = ft_strlen(key) + 1;
	free(key);
	return (g_env[key_idx] + val_idx);
}

void	init_env(char **env)
{
	g_env = (char **)ft_dup_doublestr(env);
}
