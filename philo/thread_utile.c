/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:23:26 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/06 20:21:47 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	get_time(t_philo *philo)
{
	struct timeval	mytime;
	long			time;

	gettimeofday(&mytime, NULL);
	time = (mytime.tv_sec * 1000) + mytime.tv_usec / 1000;
	return (time - philo->start_time);
}

void	end_eat(t_philo *philo)
{
	struct timeval	mytime;
	long			time;

	printf("%ld %d is eating\n", get_time(philo), philo->philo_num);
	philo->start_starve = get_time(philo);
	pthread_mutex_unlock(philo->mutex);
	if (philo->eat_time > philo->die_time)
	{
		usleep(philo->die_time * 1000);
		pthread_mutex_lock(philo->mutex);
		if (check_live_in_mutex(philo) == DIE)
			return ;
		return (philo_starve(philo));
	}
	usleep(philo->eat_time * 1000);
	pthread_mutex_lock(philo->mutex);
	if (check_live_in_mutex(philo) == DIE)
		return ;
	*(philo->left_fork) = UNUSED;
	*(philo->right_fork) = UNUSED;
	(philo->eat_count)++;
	pthread_mutex_unlock(philo->mutex);
}

int	get_fork(int eat_time, t_philo *philo)
{
	int				*fork;
	long			time;

	if (eat_time == FIRST_EAT)
	{
		if (philo->philo_num % 2 == 0)
			fork = philo->left_fork;
		else
			fork = philo->right_fork;
	}
	else
	{
		if (philo->philo_num % 2 == 0)
			fork = philo->right_fork;
		else
			fork = philo->left_fork;
	}
	if (*fork == UNUSED)
	{
		time = get_time(philo);
		printf("%ld %d has taken a fork\n", time, philo->philo_num);
		*fork = USE;
		return (TRUE);
	}
	return (0);
}
