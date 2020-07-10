#include "minishell.h"

void	print_error(char *error_token, char *msg, int res)
{
	ft_putstr_fd(SHELL, 2);
	if (!ft_strcmp(msg, LEXER_MSG))
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(error_token, 2);
		ft_putendl_fd("\'", 2);
	}
	else if (!ft_strcmp(msg, REDIR_AMB_MSG) || !ft_strcmp(msg, REDIR_FDERR_MSG)
	|| !ft_strcmp(msg, PERMISSION_MSG))
	{
		ft_putstr_fd(error_token, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(msg, 2);
	}
	g_res = res;
}

void	error_cmd(char *cmd, char *arg)
{
	ft_putstr_fd("mongshell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	g_res = 1;
	return ;
}
