/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 19:21:30 by eunhkim           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/06/26 21:42:48 by eunhkim          ###   ########.fr       */
=======
/*   Updated: 2020/06/26 22:07:58 by iwoo             ###   ########.fr       */
>>>>>>> c4cdd7242e00f8011db377588cd55dd821381fcb
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"

# define TRUE	 1
# define FALSE	 0

char	**g_env;

/*
** display functions
*/
void	clear_terminal(void);
int		print_ascii_art(void);
void	display_logo(void);
void	display_prompt(void);

/*
** bin/env functions
*/
void	init_env(char **env);
char	*get_env(char *key);
int		set_env(char *key, char *val);

# endif
