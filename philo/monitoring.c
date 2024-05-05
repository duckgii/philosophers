/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duckgi <duckgi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:28 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/05 19:02:36 by duckgi           ###   ########.fr       */
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
		// printf("123\n");
		if (one_die(monitor->philo, monitor->philo_count))
		{
			all_die(monitor->philo, monitor->philo_count);
			break ;
		}
		// printf("123123123123123123\n");
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
		// printf("%d\n", idx);
		pthread_mutex_lock(philo[idx]->mutex);
		if (philo[idx]->live == DIE)
		{
			pthread_mutex_unlock(philo[idx]->mutex);
			return (TRUE);
		}
		pthread_mutex_unlock(philo[idx]->mutex);
		idx++;
	}
	// printf("3333\n");
	return (FALSE);
}

static void	all_die(t_philo **philo, int count)
{
	int				idx;
	long			time;

	idx = 0;
	while (idx < count)
	{
		pthread_mutex_lock(philo[idx]->mutex);
		if (philo[idx]->live == ALIVE)
		{
			philo[idx]->live = DIE;
			time = get_time(philo[idx]);
			printf("%ld %d died\n", time, philo[idx]->philo_num);
			*(philo[idx]->left_fork) = UNUSED;
			*(philo[idx]->right_fork) = UNUSED;
		}
		pthread_mutex_unlock(philo[idx]->mutex);
		idx++;
	}
}

static int	all_eat(t_philo **philo, int count)
{
	int		idx;

	idx = 0;
	if (philo[0]->must_eat_count == -1)
		return (FALSE);
	while (idx < count)
	{
		pthread_mutex_lock(philo[idx]->mutex);
		// printf("%d : %d\n", philo[idx]->philo_num, philo[idx]->eat_count);
		if (philo[idx]->eat_count < (philo[idx])->must_eat_count)
		{
			pthread_mutex_unlock(philo[idx]->mutex);
			return (FALSE);
		}
		pthread_mutex_unlock(philo[idx]->mutex);
		idx++;
	}
	return (TRUE);
}
