/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 20:23:32 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/14 19:46:39 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_BONUS_H
# define MACRO_BONUS_H

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
# define HISTORY_PATH	"config/history.txt"
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
# define NOT_PRINT_ASCII	"Failed print ascii art"
# define LEXER_ERROR		"syntax error near unexpected token `"
# define REDIR_AMBIGOUS		"ambiguous redirect"
# define NO_SUCH_ENTRY		"No such file or directory"
# define PERMISSION_DENIED	"permission denied"
# define FORK_FAILED		"Fork failed for new process"
# define NOT_CMD_FOUND		"command not found"
# define EXECUTE_DRECTORY	"is a directory"
# define TOO_MANY_ARG		": too many arguments"
# define FAIL_TO_GET_PATH	": Faild to get path, check 'PWD_BUFFER_SIZE'"
# define NUMERIC_REQUIRED	": numeric argument required"
# define INVALID_IDENTIFIER	"\': not a valid identifier"

/*
** builtin command flag
** PWD_BUFFER_SIZE -> pwd
*/
# define PWD_BUFFER_SIZE 300

/*
** color
*/
# define KNRM "\x1B[0m"
# define KRED "\x1B[31m"
# define KGRN "\x1B[32m"
# define KYEL "\x1B[33m"
# define KBLU "\x1B[34m"
# define KMAG "\x1B[35m"
# define KCYN "\x1B[36m"
# define KWHT "\x1B[37m"

/*
** termcaps arg
*/
# define MAX_CMD_LEN	4096
# define MAX_KEY_LEN 4

/*
** termcaps KEY_STRING
*/
# define KEY_CODE_UP "\x1b\x5b\x41\0"
# define KEY_CODE_DO "\x1b\x5b\x42\0"
# define KEY_CODE_RI "\x1b\x5b\x43\0"
# define KEY_CODE_LE "\x1b\x5b\x44\0"

# define KEY_CODE_DEL "\x1b\x5b\x33\x7e"

# define KEY_CODE_HOME "\x1b\x5b\x48\0"
# define KEY_CODE_END "\x1b\x5b\x46\0"

# define KEY_CODE_SUP "\x1b\x1b\x5b\x41"
# define KEY_CODE_SDO "\x1b\x1b\x5b\x42"
# define KEY_CODE_SRI "\x1b\x1b\x5b\x43"
# define KEY_CODE_SLE "\x1b\x1b\x5b\x44"

# define KEY_CTRLL 12
#endif
