/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 19:58:20 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/13 21:05:47 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <string.h>
# include <termcap.h>
# include "libft.h"
# include "get_next_line.h"
# include "macro_bonus.h"
# include "types_bonus.h"
# include "termcaps_bonus.h"

char	**g_env;
int		*g_pipes;
int		g_res;
int		g_maxfd;
int		g_fd;

/*
** display functions
*/
void	display_logo(void);
void	display_prompt(void);

/*
** tokenizer function
*/
char	*escaper(char *old_line);
char	**tokenizer(char *line);

/*
** lexer function
*/
char	type(char **tokens, int idx);
int		token_in(char **tokens, t_lexer *lex, char *format);
int		lexer(char **tokens);

/*
** parser functions
*/
t_table	*get_last_table(t_table *table);
t_job	*get_last_job(t_table *table);
t_redir	*get_last_redir(t_table *table);
void	set_redir_file(char **tokens, t_lexer *lexer, \
		t_table *table);
void	set_command_cmd(char **tokens, t_lexer *lexer, \
		t_parser *parser, t_table *table);
void	set_command_arg(char **tokens, t_lexer *lexer, \
		t_table *table);
t_table	*parser(char **tokens);

/*
** converter
*/
char	**get_entries(char *src);
void	expander(t_table *table);
void	converter(t_table *table);
char	*get_config_path(char *filepath);
void	convert_heredoc(t_redir *redir);

/*
** bin/env functions
*/
int		get_key_idx(char *key);
void	init_env(int ac, char *av[], char **env);
char	*get_env(char *key);
int		set_env(char *key, char *val);

/*
** bin/builtin functions
*/
void	cmd_echo(t_command *command);
void	cmd_env(t_command *command);
void	cmd_pwd(void);
void	cmd_export(t_command *command);
void	cmd_unset(t_command *command);
void	cmd_exit(t_command *command);
void	cmd_cd(t_command *command);

/*
** execute functions with fd
*/
int		get_fd(t_redir *redir);
void	save_standard_fd(t_table *table);
void	redirect_stdout_fd(t_table *table);
void	restore_standard_fd(t_table *table);
void	close_fd_and_pipes(void);

/*
** execute functions with pipe
*/
void	dup_pipe(t_job *job, int pidx);
int		*make_pipes(t_job *job);

/*
** main execute functions
*/
void	execute_table(t_table *table);
void	cmd_execve(t_command *command);
void	set_res(int res);
void	ft_exit(char *line, int status);

/*
** signal functions
*/
void	set_builtin_signal(void);
void	set_exec_signal(void);

/*
** free functions
*/
void	free_tables(t_table *table);

/*
** print functions
*/
void	error_builtin(char *cmd, char *arg, char *msg);
void	error_tokenizer(char *error_token, char *msg, int res);
void	error_execute(char *error_token, char *msg, int res);

/*
** debug functions
*/
void	print_table(t_table *table);

#endif
