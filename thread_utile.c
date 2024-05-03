/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:23:26 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/03 16:30:43 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	get_time(t_philo *philo)
{
	struct timeval	mytime;
	long			time;

	gettimeofday(&mytime, NULL);
	time = (mytime.tv_sec * 1000) + (mytime.tv_usec % 1000000) / 1000;
	return (time - philo->start_time);
}



void	end_eat(t_philo *philo)
{
	struct timeval	mytime;
	long			time;

	time = get_time(philo);
	printf("%ld %d is eating\n", time, philo->philo_num);
	usleep(philo->eat_time * 1000);
	*(philo->left_fork) = UNUSED;
	*(philo->right_fork) = UNUSED;
	philo->start_starve = get_time(philo);
	pthread_mutex_unlock(philo->mutex);
}

int	get_fork(int eat_time, t_philo *philo)
{
	long			time;
	int				*fork;

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
		return (1);
	}
	return (0);
}

void	mutex_lock_and_think(t_philo *philo)
{
	struct timeval	mytime;
	long			time;

	pthread_mutex_lock(philo->mutex);
	time = get_time(philo);
	printf("%ld %d is thinking\n", time, philo->philo_num);
}
