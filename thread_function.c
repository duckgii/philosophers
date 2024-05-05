/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duckgi <duckgi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:22:52 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/05 19:03:30 by duckgi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	philo_eat(t_philo	*philo);
void		philo_sleep(t_philo	*philo);

void	*thread_function(void *arg)
{
	t_philo			*philo;
	long			time;
	int				idx;

	idx = 0;
	philo = (t_philo *)arg;
	philo->start_time = get_time(philo);
	philo->start_starve = 0;
	start_philo(philo);
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
			break;
	}
	return ;
}

static void	philo_eat(t_philo	*philo)
{
	int				check;
	long			time;

	check = FALSE;
	pthread_mutex_lock(philo->mutex);
	if (philo->live == DIE)
	{
		pthread_mutex_unlock(philo->mutex);
		return ;
	}
	printf("%ld %d is thinking\n", get_time(philo), philo->philo_num);
	while (check == FALSE)
	{
		time = get_time(philo);
		if (time - philo->start_starve > philo->die_time)
		{
			philo->live = DIE;
			time = get_time(philo);
			printf("%ld %d died\n", time, philo->philo_num);
			*(philo->left_fork) = UNUSED;
			*(philo->right_fork) = UNUSED;
			pthread_mutex_unlock(philo->mutex);
			return ;
		}
		check = get_fork(FIRST_EAT, philo);
	}
	check = FALSE;
	while (check == FALSE)
	{
		time = get_time(philo);
		if (time - philo->start_starve > philo->die_time)
		{
			philo->live = DIE;
			time = get_time(philo);
			printf("%ld %d died\n", time, philo->philo_num);
			*(philo->left_fork) = UNUSED;
			*(philo->right_fork) = UNUSED;
			pthread_mutex_unlock(philo->mutex);
			return ;
		}
		check = get_fork(SECOND_EAT, philo);
	}
	end_eat(philo);
}

void	philo_sleep(t_philo	*philo)
{
	long			time;

	pthread_mutex_lock(philo->mutex);
	if (philo->live == DIE)
	{
		pthread_mutex_unlock(philo->mutex);
		return ;
	}
	time = get_time(philo);
	printf("%ld %d is sleeping\n", time, philo->philo_num);
	pthread_mutex_unlock(philo->mutex);
	if (philo->eat_time + philo->sleep_time > philo->die_time)
	{
		usleep((philo->die_time - philo->eat_time) * 1000);
		return ;
	}
	usleep(philo->sleep_time * 1000);
}

//void	phlio_die(t_philo *philo, long time)
//{
//	printf("%ld %d died\n", time, )
//	pthread_mutex_destroy(philo->mutex);
//}
