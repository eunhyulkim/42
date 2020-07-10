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
	set_res(res);
}

void	error_builtin(char *cmd, char *arg)
{
	int error_num;

	error_num = errno;
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(error_num), 2);
	ft_putstr_fd("\n", 2);
	set_res(1);
	return ;
}
