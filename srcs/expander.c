#include "minishell.h"

static void		expand_command(t_command *command)
{
	char	**paths;

	if (!(paths = get_paths(command->cmd)))
		return ;
	ft_free(command->cmd);
	command->cmd = ft_strdup(paths[0]);
	ft_free_doublestr(paths);
	return ;
}

static void		expand_argument(t_command *command)
{
	int		i;
	int		j;
	char	**paths;
	char	**new_args;

	i = 0;
	paths = 0;
	new_args = 0;
	while (command->arg_list[i])
	{
		if ((paths = get_paths(command->arg_list[i])))
		{
			j = 0;
			while (paths[j])
				ft_realloc_doublestr(&new_args, paths[j++]);
		}
		i++;
	}
	if (!new_args)
		return ;
	ft_free_doublestr(command->arg_list);
	command->arg_list = new_args;
	return ;
}

static void		expand_redirection(t_redir *redir)
{
	char	**paths;

	if (!(paths = get_paths(redir->arg)))
		return ;
	if (ft_len_doublestr(paths) > 1)
		redir->error = 1;
	else
		redir->arg = ft_strdup(paths[0]);
	ft_free_doublestr(paths);
	return ;
}

static void		expand_job(t_job *job)
{
	t_redir		*redir;
	t_command	*command;

	command = &job->command;
	if (command)
		expand_command(command);
	if (command->arg_list)
		expand_argument(command);
	if (!job->redir_list)
		return ;
	redir = job->redir_list;
	while (redir)
	{
		if (ft_strcmp(redir->sign, "<<") && redir->arg)
			expand_redirection(redir);
		redir = redir->next;
	}
}

void	expander(t_table *table)
{
	t_job 	*job;

	job = table->job_list;
	while (job)
	{
		expand_job(job);
		job = job->next;
	}
	return ;
}
