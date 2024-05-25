/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:59:01 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/25 22:24:21 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>
# include <semaphore.h>

typedef struct s_info {
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		must_eat_count;
	int		live;
	int		printable;
	int		eat_finish_count;
	int		philo_count;
	int		get_fork_count;
	long	start_time;
}	t_info;

typedef struct s_philo{
	long	start_time;
	long	start_starve;
	long	start_print;
	int		eat_count;
	int		philo_num;
	sem_t	*fork;
	sem_t	*start_wait;
	sem_t	*print;
	sem_t	*all_eat;
}	t_philo;

enum {
	FALSE = 0,
	TRUE,
	ALIVE,
	DIE,
	USE,
	UNUSED,
	PRINTABLE,
	NOT_PRINTABLE,
};

void	*ft_malloc(int size);
int		ft_atoi(const char *str);
void	child_main(t_philo *philo, t_info *info);
t_philo	*parse_philo(int ac, char *av[]);
long	get_time(t_philo *philo);

#endif