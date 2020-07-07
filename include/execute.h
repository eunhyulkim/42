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
# define	START		0

# define	SUCCESS_RES	0

# include "minishell.h"
# include "sys/wait.h"

/*
** execute functions
*/

void	close_fd(void);
int		execute_table(t_table *table);

/*
**	in bin directory
*/

void	cmd_echo(t_command *command);
void	cmd_env(t_command *command);
void	cmd_pwd(t_command *command);
void	cmd_export(t_command *command);
void	cmd_unset(t_command *command);
int		cmd_exit(t_command *command);
void	cmd_cd(t_command *command);

void	cmd_execve(t_command *command);

# endif
