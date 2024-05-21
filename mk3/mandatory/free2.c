/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:30:11 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/21 09:53:52 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	free_info(t_info *info, int count);

int	free_philo(t_philo **philo)
{
	int		count;
	int		idx;

	idx = 0;
	count = philo[0]->info->philo_count;
	free_info(philo[0]->info, count);
	while (idx < count)
	{
		free(philo[idx]);
		idx++;
	}
	return (1);
}

static void	free_info(t_info *info, int count)
{
	int		idx;

	idx = 0;
	free(info->fork);
	free_malloc_mutex(info->mutex_info, MUTEX_SIZE);
	//free(info->mutex_live);
	//free(info->mutex_all_eat);
	//free(info->mutex_printable);
	while (idx < count)
	{
		free(info->mutex_fork[idx]);
		idx++;
	}
	free(info->mutex_fork);
}

int	free_philo_threads(t_philo **philo, pthread_t **threads)
{
	int		idx;
	int		count;

	idx = 0;
	count = philo[0]->info->philo_count;
	free_philo(philo);
	while (idx < count)
	{
		free(threads[idx]);
		idx++;
	}
	return (1);
}
