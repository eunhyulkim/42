/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwoo <iwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 22:12:34 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/10 22:12:47 by iwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_arg(char *key)
{
	int		idx;

	if (!key || !(*key) || ft_strchr(key, '='))
		return (FALSE);
	if ((idx = get_key_idx(key)) == -1)
		return (TRUE);
	if (!(g_env = ft_remove_doublestr(g_env, idx)))
		return (FALSE);
	return (TRUE);
}

void		cmd_unset(t_command *command)
{
	int		i;

	if (!command->arg_list)
	{
		g_res = 0;
		return ;
	}
	i = 0;
	while (command->arg_list[i])
	{
		if (!unset_arg(command->arg_list[i]))
			error_builtin("unset", command->arg_list[i], INVALID_IDENTIFIER);
		else
			g_res = (g_res == 1) ? 1 : 0;
		i++;
	}
	return ;
}
