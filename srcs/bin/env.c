/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwoo <iwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 20:27:07 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/10 21:33:10 by iwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_key_idx(char *key)
{
	int		idx;

	idx = 0;
	while (g_env[idx])
	{
		if (ft_startswith(g_env[idx], key))
		{
			if (*(g_env[idx] + ft_strlen(key)) == '=')
				return (idx);
		}
		idx++;
	}
	return (-1);
}

int		set_env(char *key, char *val)
{
	int		idx;
	char	*item;

	if (!key || !(*key))
		return (FALSE);
	idx = get_key_idx(key);
	key = ft_strjoin(key, "=");
	item = ft_strjoin(key, val);
	ft_free(key);
	if (idx == -1)
	{
		ft_realloc_doublestr(&g_env, item);
		ft_free(item);
	}
	else
	{
		ft_free(g_env[idx]);
		g_env[idx] = item;
	}
	return (TRUE);
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
		ft_free(key);
		return (0);
	}
	val_idx = ft_strlen(key) + 1;
	ft_free(key);
	return (g_env[key_idx] + val_idx);
}

void	init_env(int ac, char *av[], char **env)
{
	(void)ac;
	(void)av;
	g_stdin = 1;
	set_res(0);
	g_maxfd = 2;
	g_env = (char **)ft_dup_doublestr(env);
}

void	cmd_env(t_command *command)
{
	int		i;

	if (command->arg_list)
		return (error_builtin("env", command->arg_list[0], TOO_MANY_ARG));
	i = 0;
	while (g_env[i])
		ft_putendl_fd(g_env[i++], 1);
	return (set_res(0));
}
