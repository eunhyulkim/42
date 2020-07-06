#ifndef EXECUTE_H
# define EXECUTE_H

# define N_OPTION -2
# define PWD_BUFFER_SIZE 300

# define    OR          'O'
# define    AND         'A'
# define    SEMI        'Y'
# define    GREATER     'G'
# define    DGREATER    'H'
# define    LESS        'L'
# define    DLESS       'M'

# define	SUCCESS_RES	0

# include "minishell.h"
# include "sys/wait.h"

/*
** execute functions
*/

int		execute_redirection(t_job *job, int pipes[2]);
void	execute_job(t_job *job);
void	execute_table(t_table *table);

//temp functions
void	execute_table_with_single_job(t_table *table);

/*
**	in bin directory
*/

void	cmd_echo(t_command *command);
void	cmd_env(t_command *command);
void	cmd_pwd(t_command *command);
void	cmd_export(t_command *command);
void	cmd_unset(t_command *command);

# endif
