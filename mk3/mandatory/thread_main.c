/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:04:08 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/21 16:38:46 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	standby(t_philo *philo);
static void	up_fork_count(t_info *info);

void	*thread_function(void *arg)
{
	t_philo	*philo;
	int		check_start;

	check_start = 0;
	philo = (t_philo *)arg;
	lock(philo->info->mutex_info[MUTEX_LIVE]);
	unlock(philo->info->mutex_info[MUTEX_LIVE]);
	philo->start_time = philo->info->start_time;
	philo->start_starve = philo->start_starve;
	philo->start_print = philo->start_starve;
	if (philo->philo_num % 2 != 0)
		standby(philo);
	while (check_break(philo->info) == FALSE)
	{
		philo_wait_fork(philo, philo->info);
		if (check_start == 0 && philo->philo_num % 2 == 0)
			up_fork_count(philo->info);
		philo_eat(philo, philo->info);
		philo_sleep(philo, philo->info);
		usleep(100);
		if (check_start == 0)
			check_start = 1;
		philo_think(philo, philo->info);
	}
	return (NULL);
}

static void	up_fork_count(t_info *info)
{
	lock(info->mutex_info[MUTEX_START]);
	info->get_fork_count--;
	unlock(info->mutex_info[MUTEX_START]);
}


static void	standby(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	if (philo->philo_num == info->philo_count)
		return ;
	while (1)
	{
		lock(info->mutex_info[MUTEX_START]);
		if (info->get_fork_count == 0)
		{
			unlock(info->mutex_info[MUTEX_START]);
			return ;
		}
		unlock(info->mutex_info[MUTEX_START]);
		usleep(100);
	}
}
