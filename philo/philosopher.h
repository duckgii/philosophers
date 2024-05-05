/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duckgi <duckgi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:53:20 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/05 17:42:58 by duckgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include "./libft/libft.h"
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
	pthread_mutex_t	*mutex;
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

t_philo			**init_philo(int ac, char *av[]);
void			*thread_function(void *arg);
pthread_mutex_t	*mutex_init(void);
long			get_time(t_philo *philo);
void			start_philo(t_philo *philo);
void			mutex_lock_and_think(t_philo *philo);
int				get_fork(int eat_time, t_philo *philo);
void			end_eat(t_philo *philo);
void			*monitoring_thread(void *arg);
t_monitor		*init_monitor(t_philo **philo, int philo_count);
int				check_live(t_philo *philo);
void			check_and_change_live(t_philo *philo);
void			change_fork_status(t_philo *philo, int *fork, int status);
int				check_fork(t_philo *philo, int *fork);
void			up_eat_count(t_philo *philo);
int				check_eat_count(t_philo *philo);

#endif