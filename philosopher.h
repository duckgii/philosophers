/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:53:20 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/03 16:56:56 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include "./libft/libft.h"
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo{
	int				die;
	int				eat_time;
	int				sleep_time;
	int				eat_count;
	int				*left_fork;
	int				*right_fork;
	int				philo_num;
	long			start_starve;
	long			start_time;
	int				live;
	pthread_mutex_t	*mutex;
}	t_philo;

enum {
	USE = 1,
	UNUSED,
	FIRST_EAT,
	SECOND_EAT,
	ALIVE,
	DIE,
};

t_philo			**init_philo(int ac, char *av[]);
void			*thread_function(void *arg);
pthread_mutex_t	*mutex_init(void);
long			get_time(t_philo *philo);
void			start_philo(t_philo *philo);
void			mutex_lock_and_think(t_philo *philo);
int				get_fork(int eat_time, t_philo *philo);
void			end_eat(t_philo *philo);


#endif
