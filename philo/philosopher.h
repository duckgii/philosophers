/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:53:20 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/07 14:41:41 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include "../libft/libft.h"
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo{
	int				die_time;
	int				eat_time;
	int				sleep_time;
	long			start_time;
	long			start_starve;
	int				must_eat_count;
	int				eat_count;
	int				*left_fork;
	int				*right_fork;
	int				philo_num;
	int				live;
	pthread_mutex_t	*mutex_philo;
	pthread_mutex_t	*mutex_right;
	pthread_mutex_t	*mutex_left;
}	t_philo;

typedef struct s_monitor{
	t_philo	**philo;
	int		philo_count;
}	t_monitor;

enum {
	USE = 1,
	UNUSED,
	FIRST_EAT,
	SECOND_EAT,
	ALIVE,
	DIE,
};

enum {
	FALSE = 0,
	TRUE,
};

t_philo			**init_philo(int ac, char *av[], int *fork);
int				*fork_init(int size);
void			*thread_function(void *info);
long			get_time(t_philo *philo);
void			start_philo(t_philo *philo);
void			mutex_lock_and_think(t_philo *philo);
int				get_fork(int eat_time, t_philo *philo);
void			end_eat(t_philo *philo);
void			*monitoring_thread(void *info);
t_monitor		*init_monitor(t_philo **philo, int philo_count);
int				check_live(t_philo *philo);
void			check_and_change_live(t_philo *philo);
void			up_eat_count(t_philo *philo);
void			philo_eat(t_philo	*philo);
void			philo_starve(t_philo *philo);
void			philo_sleep(t_philo	*philo);
int				free_fork(int *fork);
int				free_philo_fork(t_philo **ret, int count, int *fork);
int				free_philo_monitor_fork(t_philo **philo, t_monitor *monitor, \
				int count, int *fork);
int				check_live_in_mutex(t_philo *philo);
void			*free_philo(t_philo **ret, int count);

#endif