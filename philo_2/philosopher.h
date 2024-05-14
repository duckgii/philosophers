/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:21:48 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/14 21:00:18 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include "../libft/libft.h"
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info {
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat_count;
	int				live;
	int				eat_finish;
	int				philo_count;
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
	int				live;
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

pthread_mutex_t	**init_fork_mutex(int count);
pthread_t		*init_threads(int count);
int				*init_fork(int count);
t_info			*init_info(int ac, char *av[]);
t_philo			**init_philo(int *fork, int count, t_info *info);
void			init_first_philo(t_philo **philo, int count);
int				free_fork_info_philo_threads(int *fork, t_info *info, \
								t_philo **philo, pthread_t *threads);
void			*free_one(void	*target);
int				free_fork(int *fork);
int				free_fork_mutex(pthread_mutex_t **fork, int count);
void			*free_philo(t_philo **philo, int count);
int				free_fork_info(int *fork, t_info *info);
int				free_fork_info_philo(int *fork, t_info *info, t_philo **philo);
void			*thread_function(void *info);
void			philo_starve(t_philo *philo);
int				get_first_fork(t_philo *philo);
int				get_second_fork(t_philo *philo);
long			get_time(t_philo *philo);
int				philo_die(t_philo *philo);
int				check_die_in_usleep(t_philo *philo, int time);
void			check_and_change_die(t_philo *philo);
void			change_fork_status(int *fork, int status, \
				pthread_mutex_t *mutex);
int				check_info_die(t_info *info);
void			lock(pthread_mutex_t *mutex);
void			unlock(pthread_mutex_t *mutex);
void			check_all_eat(t_info *info, t_philo *philo);

#endif