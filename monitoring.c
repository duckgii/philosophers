/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:28 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/03 22:44:12 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	one_die(t_philo **philo, int count);
static void	all_die(t_philo **philo, int count);
static int	all_eat(t_philo **philo, int count);

void	*monitoring_thread(void *arg)
{
	t_monitor	*monitor;
	t_philo		**philo;

	monitor = (t_monitor *)arg;
	philo = monitor->philo;
	while (1)
	{
		if (one_die(monitor->philo, monitor->philo_count))
		{
			all_die(monitor->philo, monitor->philo_count);
			break ;
		}
		if (all_eat(monitor->philo, monitor->philo_count))
		{
			all_die(monitor->philo, monitor->philo_count);
			break ;
		}
	}
	return (NULL);
}

static int	one_die(t_philo **philo, int count)
{
	int		idx;

	idx = 0;
	while (idx < count)
	{
		pthread_mutex_lock((philo[idx])->mutex);
		if ((philo[idx])->live == DIE)
		{
			printf("%dQQQQQ!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", (philo[idx])->philo_num);
			pthread_mutex_unlock((philo[idx])->mutex);
			return (1);
		}
		pthread_mutex_unlock((philo[idx])->mutex);
		idx++;
	}
	return (0);
}

static void	all_die(t_philo **philo, int count)
{
	int				idx;
	long			time;

	idx = 0;
	while (idx < count)
	{
		pthread_mutex_lock((philo[idx])->mutex);
		if ((philo[idx])->live == ALIVE)
		{
			(philo[idx])->live = DIE;
			*((philo[idx])->left_fork) = UNUSED;
			*((philo[idx])->right_fork) = UNUSED;
			time = get_time(philo[idx]);
			printf("%ld %d died\n", time, (philo[idx])->philo_num);
			pthread_mutex_unlock((philo[idx])->mutex);
		}
		pthread_mutex_unlock((philo[idx])->mutex);
		idx++;
	}
}

static int	all_eat(t_philo **philo, int count)
{
	int		idx;

	idx = 0;
	while (idx < count)
	{
		pthread_mutex_lock((philo[idx])->mutex);
		if ((philo[idx])->eat_count < (philo[idx])->must_eat_count)
		{
			pthread_mutex_unlock((philo[idx])->mutex);
			return (0);
		}
		pthread_mutex_unlock((philo[idx])->mutex);
		idx++;
	}
	return (1);
}
