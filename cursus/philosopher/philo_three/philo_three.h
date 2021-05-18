/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 10:58:43 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/21 00:55:06 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

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

# define NAME_WRITE		"/philo3_write"
# define NAME_DWRITE	"/philo3_dwrite"
# define NAME_DIED		"/philo3_died"
# define NAME_FORK		"/philo3_fork"
# define NAME_SOPHER	"/philo3_sopher"
# define NAME_EAT		"/philo3_eat"

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

typedef struct			s_semaphore
{
	sem_t				*write_s;
	sem_t				*dwrite_s;
	sem_t				*dead_s;
	sem_t				*fork_s;
	sem_t				**eat_s;
	sem_t				**sopher_s;
}						t_semaphore;

typedef struct			s_sopher
{
	int					seat_no;
	pid_t				pid;
	int					last_time;
	int					is_eating;
	int					count_eat;
	struct s_info		*info;
	struct s_semaphore	*semaphore;
}						t_sopher;

int						g_fd;
int						g_rfd;

int						sem_getvalue(sem_t *restrict sem, int *restrict sval);
/*
** parse and init functions
*/
int						parse(int ac, char *av[], t_info *info);
char					*get_semname(int i, char type);
int						init_semaphore(t_semaphore **semaphore, t_info *info);
int						init_philosophers(t_sopher	**sophers_ref, \
						t_info *info, t_semaphore *semaphore);

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
int						philosophy_three(t_info *info);

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
int						free_semaphore(t_semaphore *semaphore);
void					close_and_unlink_semaphore(t_info *info, \
						t_semaphore *sem);
void					safe_escape(t_info *info, t_semaphore *semaphore, \
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
char					*ft_strdup(const char *src);
char					*ft_strmjoin(char *s1, char *s2);
char					*ft_itoa(t_llint n);

#endif
