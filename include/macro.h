/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 20:23:32 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/10 19:55:13 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

/*
** bool
*/
# define TRUE	 		1
# define FALSE	 		0
# define NONE			0

/*
** fd
*/
# define STDIN			0
# define STDOUT			1
# define STDNRM			0
# define FDERR			-1
# define REDIRAMB		-2

/*
** file path
*/
# define TEMP_PATH		"config/temp.txt"
# define ASCIIART_PATH	"config/mongshell_ascii_art"

/*
** debug option
*/
# define DEBUG_ALL		0
# define DEBUG_LEXER		0
# define DEBUG_PARSER	0
# define DEBUG_TABLE		0
# define DEBUG_CONVERT	0

/*
** meta character
*/
# define DSEMI			'Z'
# define PIPE			'P'
# define OR      		'O'
# define AND     		'A'
# define SEMI    		'Y'
# define EMPER   		'E'
# define GREATER 		'G'
# define DGREATER		'H'
# define LESS    		'L'
# define DLESS   		'M'
# define SPACE   		'S'
# define NUMBER  		'N'
# define STRING  		'C'
# define ENTER   		'F'

/*
** TODO: add explain
** meta characters pattern
*/
# define FRONT_REDIR		"G-*,SG-*,H-*,SH-*,L-*,SL-*,M-*,SM-*"
# define FRONT_REDIR_BACK_X	"G-X,SG-X,H-X,SH-X,L-X,SL-X,M-X,SM-X"
# define FRONT_EMP_REDIR	"EG-*,EH-*,EL-*,EM-*"
# define FRONT_ALNUM		"N-*,C-*,SN-*,SC-*"
# define BACK_REDIR			"*-G,*-SG,*-H,*-SH,*-L,*-SL,*-M,*-SM"
# define NO_BACK_ARG		"*-X,*-SX,*-F,*-SF"
# define BACK_X_GREAT		"*-G,*-H"

/*
** error msg
*/
# define SHELL				"mongshell: "
# define LEXER_MSG			"syntax error near unexpected token `"
# define REDIR_AMB_MSG		"ambiguous redirect"
# define NOT_FOUND_MSG		"No such file or directory"
# define PERMISSION_MSG		"permission denied"
# define FORK_MSG			"Fork failed for new process"
# define NOT_CMD_MSG			"command not found"
# define ISDRR_MSG			"is a directory"

/*
** builtin command flag
** PWD_BUFFER_SIZE -> pwd
*/
# define PWD_BUFFER_SIZE 300

/*
** color
*/
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

#endif
