/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:09:30 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/14 21:38:47 by yeoshin          ###   ########.fr       */
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
	if (check_info_live(philo->info) == DIE || \
		check_all_eat(philo->info) == TRUE)
		return (DIE);
	usleep(time * 1000);
	if (check_info_live(philo->info) == DIE || \
		check_all_eat(philo->info) == TRUE)
		return (DIE);
	return (ALIVE);
}
