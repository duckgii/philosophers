/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:04:08 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/18 10:47:38 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*thread_function(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	lock(philo->info->mutex_live);
	unlock(philo->info->mutex_live);
	philo->start_time = philo->info->start_time;
	philo->start_starve = get_time(philo);
	if (philo->philo_num % 2 == 0)
		usleep(5000);
	while (1)
	{
		if (philo_think(philo, philo->info) == DIE)
			break ;
		philo_wait_fork(philo, philo->info);
		philo_eat(philo, philo->info);
		if (check_break(philo->info) == TRUE)
			break ;
		philo_sleep(philo, philo->info);
		if (check_break(philo->info) == TRUE)
			break ;
		usleep(100);
	}
	return (NULL);
}
