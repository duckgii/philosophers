/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utile_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:44:26 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/26 04:49:14 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	philo_wait_fork(t_philo *philo, t_info *info)
{
	int		count;

	count = 0;
	while (count < 2)
	{
		sem_wait(philo->fork);
		if ((get_time(philo) - philo->start_starve) / 1000 >= info->die_time)
			philo_starve(philo, info);
		print_get_fork(philo);
		usleep(100);
		count++;
	}
}

void	print_get_fork(t_philo *philo)
{
	sem_wait(philo->print);
	printf("%ld %d has taken a fork\n", get_time(philo) / 1000, \
	philo->philo_num);
	sem_post(philo->print);
}

void	print_philo_eat(t_philo *philo)
{
	sem_wait(philo->print);
	printf("%ld %d is eating\n", get_time(philo) / 1000, \
	philo->philo_num);
	sem_post(philo->print);
}

void	print_philo_sleep(t_philo *philo)
{
	sem_wait(philo->print);
	philo->start_print = get_time(philo);
	printf("%ld %d is sleeping\n", philo->start_print / 1000, \
	philo->philo_num);
	sem_post(philo->print);
}

void	exact_usleep(t_philo *philo, int time)
{
	usleep(time * 800);
	time = time * 1000;
	while (TRUE)
	{
		if (time <= get_time(philo) - philo->start_print)
			break ;
		usleep(100);
	}
}
