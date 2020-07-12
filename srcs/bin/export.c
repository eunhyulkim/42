/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 22:37:39 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/11 22:41:29 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_sorted_env(void)
{
	char	**sort_env;
	int		i;

	sort_env = ft_dup_doublestr(g_env);
	ft_sort_doublestr(sort_env, 0, ft_len_doublestr(g_env) - 1);
	i = -1;
	while (sort_env[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(sort_env[i], 1);
	}
	ft_free_doublestr(&sort_env);
	set_res(0);
	return ;
}

static int	export_arg(char *arg)
{
	char	*mid;
	char	*key;
	char	*val;

	if (!arg || ft_isnum(arg[0]) || ft_isset(arg[0], "=+"))
		return (FALSE);
	if (!(mid = ft_strchr(arg, '=')))
		return (TRUE);
	key = ft_strsub(arg, 0, mid - arg);
	val = ft_strsub(arg, mid - arg + 1, ft_strlen(arg) - ft_strlen(key));
	set_env(key, val);
	ft_free_str(&key);
	ft_free_str(&val);
	return (TRUE);
}

void		cmd_export(t_command *command)
{
	int		i;
	int		res;
	char	**arg_list;

	i = 0;
	res = 0;
	if (!command->arg_list)
		print_sorted_env();
	else
	{
		arg_list = command->arg_list;
		while (arg_list[i])
		{
			if (!export_arg(arg_list[i]))
				error_builtin("export", arg_list[i], INVALID_IDENTIFIER);
			else
				res = (res == 1) ? 1 : 0;
			i++;
		}
	}
	set_res(res);
	return ;
}
