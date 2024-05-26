/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:59:01 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/26 13:34:19 by yeoshin          ###   ########.fr       */
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
# include <sys/stat.h>

typedef struct s_info {
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		must_eat_count;
	int		live;
	int		printable;
	int		eat_finish_count;
	int		philo_count;
	long	start_time;
}	t_info;

typedef struct s_philo{
	long	start_time;
	long	start_starve;
	long	start_print;
	long	adjust_time;
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
t_philo	*parse_philo(char *av[]);
t_info	*init_info(int ac, char *av[]);
void	child_main(t_philo *philo, t_info *info);
void	philo_starve(t_philo *philo, t_info *info);
void	philo_eat(t_philo *philo, t_info *info);
void	philo_sleep(t_philo *philo, t_info *info);
void	philo_think(t_philo *philo);
void	philo_wait_fork(t_philo *philo, t_info *info);
void	print_get_fork(t_philo *philo);
void	print_philo_eat(t_philo *philo);
void	print_philo_sleep(t_philo *philo);
void	print_philo_died(t_philo *philo);
void	exact_usleep(t_philo *philo, int time);
long	get_time(t_philo *philo);

#endif