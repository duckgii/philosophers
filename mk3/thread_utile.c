/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:09:30 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/15 14:37:28 by yeoshin          ###   ########.fr       */
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
	long	start_time;

	info = philo->info;
	start_time = get_time(philo);
	if (check_info_live(philo->info) == DIE || \
		check_all_eat(philo->info) == TRUE)
		return (DIE);
	usleep(time * 800);
	while (TRUE)
	{
		if (philo->info->eat_time == get_time(philo) - start_time)
			break ;
		usleep(100);
	}
	if (check_info_live(philo->info) == DIE || \
		check_all_eat(philo->info) == TRUE)
		return (DIE);
	return (ALIVE);
}
