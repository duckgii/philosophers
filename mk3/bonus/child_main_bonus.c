/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:39:40 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/26 16:10:45 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void	stand_by(t_philo *philo, t_info *info);
static void	exact_first_usleep(t_philo *philo, long time);
static void	make_monitoring_thread(t_philo *philo, t_info *info);
static void	*thread_function(void *arg);

void	child_main(t_philo *philo, t_info *info)
{
	int		check_start;

	check_start = 0;
	sem_wait(philo->start_wait);
	exact_first_usleep(philo, philo->adjust_time);
	philo->start_time += philo->adjust_time;
	philo->start_print = get_time(philo);
	philo->start_starve = philo->start_print;
	make_monitoring_thread(philo, info);
	if (philo->philo_num % 2 == 0)
		stand_by(philo, info);
	while (TRUE)
	{
		philo_wait_fork(philo, info);
		if (check_start == 0 && philo->philo_num % 2 != 0)
			sem_post(philo->start_wait);
		if (check_start == 0)
			check_start = 1;
		philo_eat(philo, info);
		philo_sleep(philo, info);
		philo_think(philo);
		usleep(100);
	}
	exit(0);
}

static void	make_monitoring_thread(t_philo *philo, t_info *info)
{
	pthread_t	thread;
	t_thread	*arg;
	int			ret;

	arg = ft_malloc(sizeof(t_thread));
	arg->info = info;
	arg->philo = philo;
	ret = pthread_create(&thread, NULL, thread_function, arg);
	if (ret != 0)
	{
		printf("info thread is failed\n");
		exit(1);
	}
}

static void	*thread_function(void *arg)
{
	t_philo		*philo;
	t_info		*info;

	philo = ((t_thread *)arg)->philo;
	info = ((t_thread *)arg)->info;
	while (TRUE)
	{
		if ((get_time(philo) - philo->start_starve) / 1000 >= info->die_time)
			philo_starve(philo, info);
		usleep(200);
	}
}

static void	stand_by(t_philo *philo, t_info *info)
{
	int		count;
	int		idx;

	count = info->philo_count / 2;
	idx = 0;
	sem_wait(philo->start_wait);
	usleep(500);
}

static void	exact_first_usleep(t_philo *philo, long time)
{
	usleep((time - get_time(philo)) * (0.8));
	while (TRUE)
	{
		if (time <= get_time(philo) - philo->start_print)
			break ;
		usleep(100);
	}
}
