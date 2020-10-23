	char *getEnv(char **env, char* wild_key)
	{
		int		key_idx;
		int		val_idx;
		char	*key;

		if (!env || !wild_key || !(*wild_key))
			return (0);
		if ((key = ft::strchr(wild_key, '=')))
			key = ft::strsub(wild_key, 0, key - wild_key);
		else
			key = ft::strdup(wild_key);
		if ((key_idx = getKeyIdx(env, key)) == -1)
		{
			ft::freeStr(&key);
			return (0);
		}
		val_idx = ft::strlen(key) + 1;
		ft::freeStr(&key);
		return (env[key_idx] + val_idx);
	}
	int getKeyIdx(char** env, char *key)
	{
		int		idx;

		idx = 0;
		while (env[idx])
		{
			if (ft::startswith(env[idx], key))
			{
				if (*(env[idx] + ft::strlen(key)) == '=')
					return (idx);
			}
			idx++;
		}
		return (-1);
	}
