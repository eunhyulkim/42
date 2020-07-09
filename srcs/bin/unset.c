#include "minishell.h"

static int		unset_arg(char *key)
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
		{
			ft_putstr_fd("mongshell: unset: `", 1);
			ft_putstr_fd(command->arg_list[i], 1);
			ft_putendl_fd("\': not a valid identifier", 1);
			g_res = 1;
		}
		else
			g_res = (g_res == 1) ? 1 : 0;
		i++;
	}
	return ;
}
