#include "minishell.h"

static void	print_sorted_env(void)
{
	char **sort_env;
	int	i;

	sort_env = ft_dup_doublestr(g_env);
	ft_sort_doublestr(sort_env, 0, ft_len_doublestr(g_env) - 1);
	i = 0;
	while (sort_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(sort_env[i], 1);
		i++;
	}
	ft_free_doublestr(sort_env);
	g_res = 0;
	exit(0);
}

static int	export_arg(char *arg)
{
	char 	*mid;
	char 	*key;
	char	*val;

	if (arg[0] >= '0' && arg[0] <= '9')
		return (FALSE);
	if (arg[0] == '=')
		return (FALSE);
	if (!(mid = ft_strchr(arg, '=')))
		return (TRUE);
	key = ft_strsub(arg, 0, mid - arg);
	val = ft_strsub(arg, mid - arg + 1, ft_strlen(arg) - ft_strlen(key));
	set_env(key, val);
	free(key);
	free(val);
	return (TRUE);
}

void		cmd_export(t_command *command)
{
	int		idx;
	int		res;

	idx = 0;
	res = 0;
	if (!command->arg_list)
		print_sorted_env();
	else
	{
		while (command->arg_list[idx])
		{
			if (!export_arg(command->arg_list[idx]))
			{
				ft_putstr_fd("mongshell: export: `", 1);
				ft_putstr_fd(command->arg_list[idx], 1);
				ft_putendl_fd("\': not a valid identifier", 1);
				res = 1;
			}
			else
				res = (res == 1) ? 1 : 0;
			idx++;
		}
	}
	g_res = res;
	return ;
}
