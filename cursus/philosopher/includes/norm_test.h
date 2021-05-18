/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 10:54:11 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 10:57:26 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORM_TEST_H
# define NORM_TEST_H

# define STDIN		0

typedef unsigned char	t_uchar;
typedef struct			s_mutex
{
	pthread_mutex_t		write_m;
	pthread_mutex_t		dead_m;
	pthread_mutex_t		*eat_m;
	pthread_mutex_t		*fork_m;
	pthread_mutex_t		*sopher_m;
}						t_mutex;

int						parse(int ac, char *av[], t_info *info);
int						init_mutex(t_mutex **mutex, t_info *info);

#endif
