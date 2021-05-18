#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include "libft.h"

# define		STDIN	0
# define		STDOUT	1
# define		STDERR	2

# define		TRUE	1
# define		FALSE	0

# define		LIVE	0
# define		THINK	1
# define		DIED	2

# define		SLEEP_ALPHA		50

typedef struct	s_tab
{
	int				numbers; // 철학자의 수
	int				time_die; // 식사 완료 이후 죽기까지 남은 시간
	int				time_eat; // 식사하는데 필요한 시간
	int				time_sleep; // 수면시간
	int				must_eat; // 먹어야 할 끼니의 수
	pthread_mutex_t	*mutex;
	int				day; // 날짜
	long			start_sec; // 시작시간
	long			start_usec; // 종료시간
	long			last_time; // 가장 최근 식사시간
	int				count_eat; // 현재까지 먹은 끼니의 수
	int				seat_no; // 고유번호
	int				order; // 식사일자
	int				status; // 상태
}					t_tab;

int				g_fd;
int				g_rfd;

int			parse(int ac, char *av[], t_tab	*tab);

void		init_philosophers(t_tab	**tab, t_tab *origin_tab);
void		init_thread(pthread_t **thread, t_tab *tab);
void		init_mutex(t_tab *tab);

void		set_start_time(t_tab *tab);
uint64_t	get_timestamp(t_tab *tab);
uint64_t	get_hungry_time(t_tab *tab);

int			get_start_order(int numbers, int seat_no);
int			get_next_order(t_tab *tab);

void		*live(void *tab_arg);
void		simulation(t_tab *tab, pthread_t *thread);

void		destroy_mutex(t_tab *tab);
void		ft_error(char *msg, void *free_item);

void		log_init_philosophers(t_tab *tab, t_tab *origin_tab);
void		log_init_thread(pthread_t *thread, t_tab *origin_tab);

#endif
