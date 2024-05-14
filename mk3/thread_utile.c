/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:09:30 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/14 20:46:01 by yeoshin          ###   ########.fr       */
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

void	lock(pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
}

void	unlock(pthread_mutex_t *mutex)
{
	pthread_mutex_unlock(mutex);
}

void	change_fork_status(int *fork, int status, pthread_mutex_t *mutex)
{
	lock(mutex);
	*fork = status;
	unlock(mutex);
}

int	check_die_in_usleep(t_philo *philo, long time)
{
	t_info	*info;

	info = philo->info;
	while (time > 0)
	{
		if (check_info_die(philo->info) == DIE)
			return (philo_die(philo));
		if (check_all_eat(philo->info) == TRUE)
			return (DIE);
		if (time > 9)
			usleep(9 * 1000);
		else
			usleep(time * 1000);
		time -= 9;
	}
	if (check_info_live(philo->info) == DIE)
	{
		philo_starve(philo, info);
		return (DIE);
	}
	if (check_all_eat(philo->info) == TRUE)
		return (DIE);
	return (ALIVE);
}
