/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 05:44:00 by jrameau           #+#    #+#             */
/*   Updated: 2020/07/08 16:45:20 by iwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

static char		**get_args(t_command *command)
{
	char	**args;
	char	*filename;
	int		idx;

	args = 0;
	if (!(filename = ft_strrchr(command->cmd, '/')))
		filename = ft_strdup(command->cmd);
	else
		filename = ft_strdup(filename);
	ft_realloc_doublestr(&args, filename);
	idx = 0;
	while (command->arg_list && command->arg_list[idx])
		ft_realloc_doublestr(&args, command->arg_list[idx++]);
	free(filename);
	return (args);
}

static void     run_exec(t_command *command)
{
    pid_t   pid;
    char    *path;
    char    **args;

    path = ft_strdup(command->cmd);
    args = get_args(command);
    pid = fork();
	signal(SIGINT, signal_handler_in_run_exec);
   	signal(SIGQUIT, signal_handler_in_run_exec);
    if (pid == 0)
		execve(path, args, g_env);
    else if (pid < 0)
    {
        ft_putendl_fd("Fork failed for new process", 1);
        return ;
    }
    wait(&pid);
	ft_free_doublestr(args);
    return ;
}

static char			*check_bins(char *cmd, char **bin_path)
{
	char			*path;
	char			*denied_path;
	struct stat		stat;
	int 			idx;

	idx = 0;
	denied_path = 0;
	while (bin_path[idx])
	{
		if (ft_startswith(cmd, bin_path[idx]))
			path = ft_strdup(cmd);
		else
			path = ft_strsjoin(bin_path[idx], "/", cmd, 0);
		if (lstat(path, &stat) == -1)
			free(path);
		else if ((stat.st_mode & S_IFREG) && (stat.st_mode & S_IXUSR))
			return (path);
		else if (stat.st_mode & S_IFREG)
		{
			ft_free(denied_path);
			denied_path = path;
		}
		idx++;
	}
	return (denied_path);
}

static void			run_exec_bin(char *path, t_command *command)
{
	struct stat		stat;

	if (lstat(path, &stat) == -1)
		return ;
	ft_free(command->cmd);
	command->cmd = path;
	if (stat.st_mode & S_IFREG && stat.st_mode & S_IXUSR)
	{
		ft_free(command->cmd);
		command->cmd = path;
		return (run_exec(command));
	}
	ft_putstr_fd("mongshell: permission denied: ", 2);
	ft_putendl_fd(path, 1);
	return ;
}

void				cmd_execve(t_command *command)
{
	struct stat		stat;
	char			**bin_path;
	char			*path;

	bin_path = ft_split(get_env("PATH"), ':');
	path = 0;
	if ((path = check_bins(command->cmd, bin_path)))
	{
		ft_free_doublestr(bin_path);
		return (run_exec_bin(path, command));
	}
	ft_free_doublestr(bin_path);
	if (lstat(command->cmd, &stat) != -1)
	{
		if (stat.st_mode & S_IFDIR)
			return (cmd_cd(command));
		else if (stat.st_mode & S_IXUSR)
			return (run_exec(command));
	}
	ft_putstr_fd("mongshell: ", 2);
	ft_putstr_fd(command->cmd, 2);
	if (!ft_strchr(command->cmd, '/'))
		ft_putendl_fd(": command not found", 2);
	else if (!(stat.st_mode & S_IXUSR))
		ft_putendl_fd(": Permission denied", 2);
	else
		ft_putendl_fd(": No such file or directory", 2);
	return ;
}
