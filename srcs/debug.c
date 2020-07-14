#include "minishell.h"

void		print_table(t_table *table)
{
	t_job	*job;
	t_redir	*redir;
	char	**arg;
	int		idx;

	if (!table)
		return ;
	int tno = 0;
	dprintf(g_fd, "\n%s%-10s%-6s%-8s%-16s%-50s%s\n", KCYN, "TABLE_NO", "TYPE", "JOB_NO", \
	"CMD", "ARG", "REDIRECT");
	while (table)
	{
		tno++;
		job = table->job_list;
		int jno = 1;
		while (job)
		{
			dprintf(g_fd, "%s%-10d", KNRM, tno);
			if (!table->sep_type)
				dprintf(g_fd, "%-6s", "START");
			else if (table->sep_type == AND)
				dprintf(g_fd, "%-6s", "AND");
			else if (table->sep_type == OR)
				dprintf(g_fd, "%-6s", "OR");
			else if (table->sep_type == SEMI)
				dprintf(g_fd, "%-6s", "SEMI");
			dprintf(g_fd, "%-8d", jno++);
			if (job->command.cmd)
				dprintf(g_fd, "%-16s", job->command.cmd);
			else
				dprintf(g_fd, "%s%-16s%s", KYEL, "Null", KNRM);
			arg = job->command.arg_list;
			idx = 0;
			int len = 0;
			if (!arg && (len = 50))
				dprintf(g_fd, "%s%-50s%s", KYEL, "Null", KNRM);
			while (arg && arg[idx])
			{
				dprintf(g_fd, "%s,", arg[idx]);
				len += ft_strlen(arg[idx]) + 1;
				idx++;
			}
			len = 50 - len;
			if (len < 0)
				len = 0;
			while (len--)
				dprintf(g_fd, " ");
			if (!job->redir_list)
				dprintf(g_fd, "%s%s%s\n", KYEL, "Null", KNRM);
			else
			{
				redir = job->redir_list;
				while (redir)
				{
					if (redir->sign[0] == '>')
						dprintf(g_fd, "%d", redir->fd);
					dprintf(g_fd, "%s", redir->sign);
					dprintf(g_fd, "%s,", redir->arg);
					redir = redir->next;
				}
				dprintf(g_fd, "\n");
			}
			job = job->next;
		}
		table = table->next;
	}
}
