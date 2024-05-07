/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:48:43 by duckgi            #+#    #+#             */
/*   Updated: 2024/05/06 22:21:22 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_live(t_philo *philo)
{
	int	flag;

	pthread_mutex_lock(philo->mutex_philo);
	if (philo->live == ALIVE)
		flag = ALIVE;
	else
		flag = DIE;
	pthread_mutex_unlock(philo->mutex_philo);
	return (flag);
}

int	check_live_in_mutex(t_philo *philo)
{
	if (philo->live == DIE)
	{
		pthread_mutex_unlock(philo->mutex_philo);
		return (DIE);
	}
	return (ALIVE);
}
