/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:00:08 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/07 13:18:06 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_first_fork(t_philo *philo)
{
	int				*fork;
	long			time;
	pthread_mutex_t	*mutex;

	if (philo->philo_num % 2 == 0)
	{
		fork = philo->left_fork;
		mutex = philo->mutex_left;
	}
	else
	{
		fork = philo->right_fork;
		mutex = philo->mutex_right;
	}
	lock(mutex);
	if (*fork == UNUSED)
	{
		printf("%ld %d has taken a fork\n", get_time(philo), philo->philo_num);
		*fork = USE;
		unlock(mutex);
		return (TRUE);
	}
	unlock(mutex);
	return (FALSE);
}

int	get_second_fork(t_philo *philo)
{
	int				*fork;
	long			time;
	pthread_mutex_t	*mutex;

	if (philo->philo_num % 2 != 0)
	{
		fork = philo->left_fork;
		mutex = philo->mutex_left;
	}
	else
	{
		fork = philo->right_fork;
		mutex = philo->mutex_right;
	}
	lock(mutex);
	if (*fork == UNUSED)
	{
		printf("%ld %d has taken a fork\n", get_time(philo), philo->philo_num);
		*fork = USE;
		unlock(mutex);
		return (TRUE);
	}
	unlock(mutex);
	return (FALSE);
}
