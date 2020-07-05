#include "minishell.h"
#include "lexer.h"

void		print_table(t_table *table)
{
	t_job	*job;
	t_redir	*redir;
	char	**arg;
	int		idx;

	if (!table)
		return ;
	int tno = 0;
	printf("%-10s%-6s%-8s%-16s%-25s%-10s%s\n", "TABLE_NO", "TYPE", "JOB_NO", \
	"CMD", "ARG", "FD", "REDIRECT");
	while (table)
	{
		tno++;
		job = table->job_list;
		int jno = 1;
		while (job)
		{
			printf("%-10d", tno);
			if (!table->sep_type)
				printf("%-6s", "START");
			else if (table->sep_type == AND)
				printf("%-6s", "AND");
			else if (table->sep_type == OR)
				printf("%-6s", "OR");
			else if (table->sep_type == SEMI)
				printf("%-6s", "SEMI");
			printf("%-8d", jno++);
			printf("%-16s", job->command.cmd);
			arg = job->command.arg_list;
			idx = 0;
			int len = 0;
			while (arg && arg[idx])
			{
				printf("%s,", arg[idx]);
				len += ft_strlen(arg[idx]) + 1;
				idx++;
			}
			len = 25 - len;
			while (len--)
				printf(" ");
			printf("[%d][%d]", job->fd[0], job->fd[1]);
			len = 0;
			len += (job->fd[0] >= 10) ? 2 : 1;
			len += (job->fd[0] >= 100) ? 1 : 0;
			len += (job->fd[1] >= 10) ? 2 : 1;
			len += (job->fd[1] >= 100) ? 1 : 0;
			len = 10 - len - 4;
			while (len--)
				printf(" ");
			if (!job->redir_list)
				printf("%s\n", "Null");
			else
			{
				redir = job->redir_list;
				while (redir)
				{
					if (redir->sign[0] == '>')
						printf("%d", redir->fd);
					printf("%s", redir->sign);
					printf("%s,", redir->arg);
					redir = redir->next;
				}
				printf("\n");
			}
			job = job->next;
		}
		table = table->next;
	}
}
