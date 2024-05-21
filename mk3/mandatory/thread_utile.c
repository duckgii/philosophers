/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:09:30 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/21 16:44:49 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	get_time(t_philo *philo)
{
	struct timeval	mytime;
	long			time;

	gettimeofday(&mytime, NULL);
	time = (mytime.tv_sec * 1000000) + mytime.tv_usec;
	return (time - philo->start_time);
}

int	get_one_fork(t_philo *philo, int *fork, pthread_mutex_t *mutex)
{
	if (mutex == NULL)
		return (FALSE);
	lock(mutex);
	if (*fork == UNUSED)
	{
		print_take_fork(philo, philo->info);
		*fork = USE;
		unlock(mutex);
		return (TRUE);
	}
	unlock(mutex);
	return (FALSE);
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
