/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 19:21:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/26 22:07:58 by iwoo             ###   ########.fr       */
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

void	init_env(char **env);
char	*get_env(char *key);

void	clear_terminal(void);
int		print_ascii_art(void);
void	display_logo(void);
void	display_prompt(void);

# endif
