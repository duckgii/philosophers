/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utile2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:44:11 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/14 21:11:55 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_first_fork(t_philo *philo)
{
	int				*fork;
	//long			time;
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
	//long			time;
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

int	check_info_live(t_info *info)
{
	lock(info->mutex_info);
	if (info->live == DIE)
	{
		unlock(info->mutex_info);
		return (DIE);
	}
	unlock(info->mutex_info);
	return (ALIVE);
}
