/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 19:55:27 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/10 19:57:45 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef int			t_bool;

/*
** tokenizer.c
*/
typedef struct			s_tokenizer
{
	int					idx;
	int					qidx;
	int					start;
	int					prev;
	char				quote;
}						t_tokenizer;

/*
** lexer.c
*/
typedef struct			s_lexer
{
	int					len;
	int					idx;
	char				type;
	char				**seqs;
	char				**format;
	int					i;
	int					j;
	int					res;
}						t_lexer;

/*
** parser.c
*/
typedef struct			s_parser
{
	int					command;
	int					fd;
}						t_parser;

/*
** table structure with almost files
*/
typedef struct			s_redir
{
	char				*sign;
	int					fd;
	int					error;
	char				*arg;
	struct s_redir		*next;
}						t_redir;

typedef struct			s_command
{
	char				*cmd;
	char				**arg_list;
	int					idx;
}						t_command;

typedef struct			s_job
{
	struct s_command	command;
	struct s_redir		*redir_list;
	struct s_job		*next;
}						t_job;

typedef struct			s_table
{
	struct s_job		*job_list;
	int					sep_type;
	int					fd[3];
	struct s_table		*next;
}						t_table;

#endif
