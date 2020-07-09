/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 21:53:10 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/09 21:53:19 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_redir_file(char **tokens, t_lexer *lexer, \
			t_table *table)
{
	t_redir		*redir;

	redir = get_last_redir(table);
	redir->arg = ft_strdup(tokens[lexer->idx]);
	return ;
}

void		set_command_cmd(char **tokens, t_lexer *lexer, \
			t_parser *parser, t_table *table)
{
	t_job		*job;

	job = get_last_job(table);
	job->command.cmd = ft_strdup(tokens[lexer->idx]);
	parser->command = TRUE;
	return ;
}

void		set_command_arg(char **tokens, t_lexer *lexer, \
			t_table *table)
{
	t_job		*job;
	char		***arg;

	job = get_last_job(table);
	arg = &job->command.arg_list;
	ft_realloc_doublestr(arg, tokens[lexer->idx]);
	return ;
}
