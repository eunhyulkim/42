/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 10:58:43 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 11:02:47 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>

# define STDIN			0
# define STDOUT			1
# define STDERR			2

# define TRUE			1
# define FALSE			0

# define TYPE_OVER		1
# define TYPE_DIED		2
# define TYPE_FORKUP 	3
# define TYPE_EAT		4
# define TYPE_SLEEP		5
# define TYPE_THINK		6

# define LIVE			0
# define THINK			1
# define DIED			2

# define SLEEP_ALPHA	50

typedef unsigned char			t_uchar;
typedef unsigned int			t_uint;
typedef unsigned long int		t_ulint;
typedef unsigned long long int	t_ullint;
typedef long double				t_ldouble;
typedef long long int			t_llint;
typedef pthread_mutex_t			t_pm;

typedef struct			s_info
{
	int					numbers;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					must_eat;
	long				start_sec;
	long				start_usec;
}						t_info;

typedef struct			s_mutex
{
	pthread_mutex_t		write_m;
	pthread_mutex_t		dead_m;
	pthread_mutex_t		*eat_m;
	pthread_mutex_t		*fork_m;
	pthread_mutex_t		*sopher_m;
}						t_mutex;

typedef struct			s_sopher
{
	int					seat_no;
	int					first_fork;
	int					second_fork;
	int					last_time;
	int					is_eating;
	int					count_eat;
	struct s_info		*info;
	struct s_mutex		*mutex;
}						t_sopher;

int						g_fd;
int						g_rfd;

/*
** parse and init functions
*/
int						parse(int ac, char *av[], t_info *info);
int						init_mutex(t_mutex **mutex, t_info *info);
int						init_philosophers(t_sopher	**sophers_ref, \
						t_info *info, t_mutex *mutex);

/*
** moniter functions
*/
void					*moniter_heart_routine(void *sopher);
void					moniter_heart(t_sopher *sophers, t_info *info);
void					*moniter_count_routine(void *sophers);
void					moniter_count(t_sopher *sophers);

/*
** simulation functions
*/
void					take_forks(t_sopher *sopher);
void					clean_forks(t_sopher *sopher);
void					eat(t_sopher *sopher);
void					*live(void *sopher);
void					simulation(t_sopher *sophers);

/*
** print functions
*/
char					*get_message(int message_type);
void					print_message(t_sopher *sopher, int message_type);

/*
** main function
*/
int						philosophy_one(t_info *info);

/*
** time utils
*/
void					set_start_time(t_info *info);
uint64_t				get_time(t_sopher *sopher);
uint64_t				get_hungry_time(t_sopher *sopher);

/*
** escape functions
*/
void					ft_error(char *msg);
int						free_mutex(t_mutex *mutex);
void					destroy_mutex(t_info *info, t_mutex *mutex);
void					safe_escape(t_info *info, t_mutex *mutex, \
						t_sopher *sophers);

/*
** basic utils
*/
void					*ft_calloc(size_t size, size_t count);
void					*ft_memset(void *data, int c, size_t len);
size_t					ft_strlen(const char *str);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putnbr_fd(t_llint n, int fd);
void					ft_putendl_fd(char *s, int fd);
int						ft_atoi(char *str);
int						ft_isnum(t_llint c);
int						ft_isset(int c, char *set);
int						ft_isnumber(char *str);

/*
** log function
*/
void					log_init_philosophers(t_info *info, t_sopher *sophers);

#endif
