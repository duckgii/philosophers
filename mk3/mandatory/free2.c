/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:30:11 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/27 13:10:53 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	free_info(t_info *info);

int	free_philo(t_philo **philo)
{
	int		count;
	int		idx;

	idx = 0;
	count = philo[0]->info->philo_count;
	free_info(philo[0]->info);
	while (idx < count)
	{
		free(philo[idx]);
		idx++;
	}
	free(philo);
	return (1);
}

static void	free_info(t_info *info)
{
	int		idx;

	idx = 0;
	free(info->fork);
	free_malloc_mutex(info->mutex_info, MUTEX_SIZE);
	free_malloc_mutex(info->mutex_fork, info->philo_count);
	free(info);
	//while (idx < count)
	//{
	//	unlock(info->mutex_fork[idx]);
	//	pthread_mutex_destroy(info->mutex_fork[idx]);
	//	free(info->mutex_fork[idx]);
	//	idx++;
	//}
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
	free(threads);
	return (1);
}
