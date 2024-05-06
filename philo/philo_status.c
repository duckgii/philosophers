/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:47:10 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/06 20:24:24 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philo_eat(t_philo	*philo)
{
	int				check;
	long			time;

	check = FALSE;
	pthread_mutex_lock(philo->mutex);
	if (check_live_in_mutex(philo) == DIE)
		return ;
	printf("%ld %d is thinking\n", get_time(philo), philo->philo_num);
	while (check == FALSE)
	{
		time = get_time(philo);
		if (time - philo->start_starve > philo->die_time)
			return (philo_starve(philo));
		check = get_fork(FIRST_EAT, philo);
	}
	check = FALSE;
	while (check == FALSE)
	{
		time = get_time(philo);
		if (time - philo->start_starve > philo->die_time)
			return (philo_starve(philo));
		check = get_fork(SECOND_EAT, philo);
	}
	end_eat(philo);
}

void	philo_sleep(t_philo	*philo)
{
	long			time;

	pthread_mutex_lock(philo->mutex);
	if (check_live_in_mutex(philo) == DIE)
		return ;
	time = get_time(philo);
	printf("%ld %d is sleeping\n", time, philo->philo_num);
	pthread_mutex_unlock(philo->mutex);
	if (philo->eat_time + philo->sleep_time > philo->die_time)
	{
		usleep((philo->die_time - philo->eat_time) * 1000);
		return ;
	}
	usleep(philo->sleep_time * 1000);
}

void	philo_starve(t_philo *philo)
{
	long	time;

	philo->live = DIE;
	time = get_time(philo);
	printf("%ld %d died\n", time, philo->philo_num);
	*(philo->left_fork) = UNUSED;
	*(philo->right_fork) = UNUSED;
	pthread_mutex_unlock(philo->mutex);
	return ;
}
