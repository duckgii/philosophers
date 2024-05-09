/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:23:01 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/09 16:21:47 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	change_fork_status(int *fork, int status, pthread_mutex_t *mutex)
{
	lock(mutex);
	*fork = status;
	unlock(mutex);
}

int	check_info_die(t_info *info)
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

void	lock(pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
}

void	unlock(pthread_mutex_t *mutex)
{
	pthread_mutex_unlock(mutex);
}

void	check_all_eat(t_info *info, t_philo *philo)
{
	lock(info->mutex_info);
	if (info->eat_finish != 0)
	{
		unlock(info->mutex_info);
		return ;
	}
	if (philo->live == ALIVE)
		philo_die(philo);
	return ;
}
