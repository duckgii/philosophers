/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duckgi <duckgi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:48:43 by duckgi            #+#    #+#             */
/*   Updated: 2024/05/05 19:01:37 by duckgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_live(t_philo *philo)
{
	int flag;

	pthread_mutex_lock(philo->mutex);
	if (philo->live == ALIVE)
		flag = ALIVE;
	else
		flag = DIE;
	pthread_mutex_unlock(philo->mutex);
	return (flag);
}

int		check_fork(t_philo *philo, int *fork)
{
	int status;

	pthread_mutex_lock(philo->mutex);
	if (*fork == UNUSED)
		status = UNUSED;
	else
		status = USE;
	pthread_mutex_unlock(philo->mutex);
	return (status);
}

// void	check_and_change_live(t_philo *philo)
// {
// 	long	time;

// 	pthread_mutex_lock(philo->mutex);
// 	if (philo->live == DIE)
// 	{
// 		pthread_mutex_unlock(philo->mutex);
// 		return ;
// 	}
// 	philo->live = DIE;
// 	pthread_mutex_unlock(philo->mutex);
// 	time = get_time(philo);
// 	printf("%ld %d died\n", time, philo->philo_num);
// 	change_fork_status(philo, philo->left_fork, UNUSED);
// 	change_fork_status(philo, philo->right_fork, UNUSED);
// }

void	change_fork_status(t_philo *philo, int *fork, int status)
{
	pthread_mutex_lock(philo->mutex);
	*fork = status;
	pthread_mutex_unlock(philo->mutex);
}

void	up_eat_count(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	philo->eat_count++;
	pthread_mutex_unlock(philo->mutex);
}

int		check_eat_count(t_philo *philo)
{
	int	eat_count;

	pthread_mutex_lock(philo->mutex);
	eat_count = philo->eat_count;
	pthread_mutex_unlock(philo->mutex);
	return (eat_count);
}
