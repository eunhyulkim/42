/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 19:21:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/26 21:42:48 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

# define TRUE	 1
# define FALSE	 0

char	**g_env;

/*
** bin/env functions
*/
void	init_env(char **env);
char	*get_env(char *key);
int		set_env(char *key, char *val);

# endif
