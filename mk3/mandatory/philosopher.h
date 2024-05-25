/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:43:20 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/25 15:27:34 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_info {
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat_count;
	int				live;
	int				printable;
	int				eat_finish_count;
	int				philo_count;
	int				get_fork_count;
	int				*fork;
	long			start_time;
	pthread_mutex_t	**mutex_fork;
	pthread_mutex_t	**mutex_info;
}	t_info;

typedef struct s_philo{
	long			start_time;
	long			start_starve;
	long			start_print;
	int				eat_count;
	int				philo_num;
	int				*left_fork;
	int				*right_fork;
	pthread_mutex_t	*mutex_right;
	pthread_mutex_t	*mutex_left;
	t_info			*info;
}	t_philo;

enum {
	FALSE = 0,
	TRUE,
	ALIVE,
	DIE,
	USE,
	UNUSED,
	FIRST_FORK,
	SECOND_FORK,
	PRINTABLE,
	NOT_PRINTABLE,
	GET_FORK_COUNT,
};

enum {
	PRINT_THINK = 0,
	PRINT_FORK,
	PRINT_EAT,
	PRINT_SLEEP,
	PRINT_DIE,
	MUTEX_LIVE,
	MUTEX_ALL_EAT,
	MUTEX_START,
	MUTEX_SIZE
};

int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
t_philo	**parse_arg(int ac, char *av[]);
void	make_one_philo(t_philo *philo, t_info *info, int idx);
t_info	*malloc_info(t_info *info, char *av[]);
void	*free_one(void	*pointer);
void	*free_malloc_philos(t_philo **ret, int count);
void	*free_malloc_mutex(pthread_mutex_t **ret, int count);
void	*free_malloc_threads(pthread_t **ret, int count);
int		free_philo(t_philo **philo);
int		free_philo_threads(t_philo **philo, pthread_t **threads);
void	*thread_function(void *arg);
int		check_all_eat(t_info *info);
void	philo_wait_fork(t_philo *philo, t_info *info);
void	philo_eat(t_philo *philo, t_info *info);
void	philo_sleep(t_philo *philo, t_info *info);
void	philo_starve(t_philo *philo, t_info *info);
long	get_time(t_philo *philo);
void	lock(pthread_mutex_t *mutex);
void	unlock(pthread_mutex_t *mutex);
void	change_fork_status(int *fork, int status, pthread_mutex_t *mutex);
int		check_die_in_usleep(t_philo *philo, long time);
int		get_one_fork(t_philo *philo, int *fork, pthread_mutex_t *mutex);
int		check_info_live(t_info *info);
void	philo_think(t_philo *philo, t_info *info);
void	print_take_fork(t_philo *philo, t_info *info);
void	print_eating(t_philo *philo, t_info *info);
void	print_sleeping(t_philo *philo, t_info *info);
int		check_break(t_info *info);

#endif