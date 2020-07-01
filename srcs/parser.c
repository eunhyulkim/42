/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 23:09:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/01 00:56:22 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"

typedef COMMAND					4;
typedef ARGUMENT				5;
typedef PIPE					10;
typedef REDIRECT				6;
typedef FILENAME				7;
typedef COMMAND_PARSE_MASK		5;
typedef REDIRECT_PARSE_MASK		7;

typedef struct 			s_command
{
	struct s_command	*next;
}						t_command;

typedef struct 			s_redirect
{
	struct s_redirect	*next;
}						t_redirect;

typedef struct  		s_table
{
	struct s_command	*commands;
	struct s_redirect	*redirects;
	bool				has_cmd;
	bool				has_redirect;
	int					in_fd;
	int					out_fd;
}						t_table;

/*
** command [arguments] | cmd [arguments] | ... | redirects filename
*/

/*
** ERROR_CASE(has_cmd, has_redirect)
** PIPE		5	0
** ARGUMENT	10	0
** COMMAND	4	1
** REDIRECT	6		1
** FILENAME	7		0
*/

t_table		*parser(char **tokens)
{
	t_parser	*parser;
	t_lexer		*lexer;
	t_table		*table;

	if (!(table = (t_table *)ft_calloc(sizeof(t_table), 1)))
		return (0);
	while (tokens[++idx])
	{
		type = check_type(table, tokens, idx);
		if (is_syntax_error(table, tokens, idx, type))
			break ;
		if (type == COMMAND || type == ARGUMENT)
			register_command(table, tokens[idx], type);
		else if (type == REDIRECT || type == FILENAME)
			register_redirect(table, tokens[idx], type);
		else if (type == PIPE)
			table->has_cmd = FALSE;
	}
	return (table);
}
