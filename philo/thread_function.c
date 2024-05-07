/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:22:52 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/07 14:41:41 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*thread_function(void *info)
{
	t_philo			*philo;
	long			time;

	philo = (t_philo *)info;
	philo->start_time = get_time(philo);
	philo->start_starve = 0;
	start_philo(philo);
	pthread_mutex_destroy(philo->mutex);
	return (NULL);
}

void	start_philo(t_philo *philo)
{
	int		idx;

	idx = 0;
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		if (check_live(philo) == DIE)
			break ;
	}
	return ;
}
