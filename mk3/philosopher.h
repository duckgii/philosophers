/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:43:20 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/14 22:27:18 by yeoshin          ###   ########.fr       */
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
	int				eat_finish_count;
	int				philo_count;
	int				*fork;
	pthread_mutex_t	**mutex_fork;
	pthread_mutex_t	*mutex_info;
}	t_info;

typedef struct s_philo{
	long			start_time;
	long			start_starve;
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
int		check_someone_die(t_info *info);
void	philo_eat(t_philo *philo, t_info *info);
void	philo_sleep(t_philo *philo, t_info *info);
void	philo_starve(t_philo *philo, t_info *info);
long	get_time(t_philo *philo);
void	lock(pthread_mutex_t *mutex);
void	unlock(pthread_mutex_t *mutex);
void	change_fork_status(int *fork, int status, pthread_mutex_t *mutex);
int		check_die_in_usleep(t_philo *philo, long time);
int		get_first_fork(t_philo *philo);
int		get_second_fork(t_philo *philo);
int		check_info_live(t_info *info);

#endif