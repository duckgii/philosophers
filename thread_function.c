/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:22:52 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/03 23:02:47 by yeoshin          ###   ########.fr       */
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
	start_philo(philo);
	return (NULL);
}

void	start_philo(t_philo *philo)
{
	int		idx;
	int		count;

	idx = 0;
	count = philo->must_eat_count;
	if (count == -1)
		idx = count - 1;
	while (idx < count)
	{
		philo_eat(philo);
		philo_sleep(philo);
		if (count != -1)
			idx++;
		//if (philo->live == DIE)
		//	break ;
	}
	return ;
}

static void	philo_eat(t_philo	*philo)
{
	int				check;
	long			time;

	mutex_lock_and_think(philo);
	check = 0;
	pthread_mutex_unlock(philo->mutex);
	while (check == 0 && philo->live == ALIVE)
	{
		pthread_mutex_lock(philo->mutex);
		time = get_time(philo);
		if (time - philo->start_starve > philo->die_time)
		{
			printf("%ld %d died\n", time, philo->philo_num);
			pthread_mutex_unlock(philo->mutex);
			pthread_mutex_lock(philo->mutex);
			philo->live = DIE;
			pthread_mutex_unlock(philo->mutex);
			return ;
		}
		check = get_fork(FIRST_EAT, philo);
	}
	check = 0;
	while (check == 0 && philo->live == ALIVE)
	{
		time = get_time(philo);
		if (time - philo->start_starve > philo->die_time)
		{
			*(philo->left_fork) = UNUSED;
			*(philo->right_fork) = UNUSED;
			printf("%ld %d died\n", time, philo->philo_num);
			pthread_mutex_unlock(philo->mutex);
			pthread_mutex_lock(philo->mutex);
			philo->live = DIE;
			pthread_mutex_unlock(philo->mutex);
			return ;
		}
		check = get_fork(SECOND_EAT, philo);
	}
	end_eat(philo);
}

void	philo_sleep(t_philo	*philo)
{
	struct timeval	mytime;
	long			time;

	pthread_mutex_lock(philo->mutex);
	if (philo->live == DIE)
	{
		pthread_mutex_unlock(philo->mutex);
		return ;
	}
	time = get_time(philo);
	printf("%ld %d is sleeping\n", time, philo->philo_num);
	if (philo->sleep_time > philo->die_time)
	{
		usleep(philo->die_time * 1000);
		printf("%ld %d died\n", time, philo->philo_num);
		philo->live = DIE;
		return ;
	}
	usleep(philo->sleep_time * 1000);
	pthread_mutex_lock(philo->mutex);
	if (philo->live == DIE)
	{
		pthread_mutex_unlock(philo->mutex);
		return ;
	}
}

//void	phlio_die(t_philo *philo, long time)
//{
//	printf("%ld %d died\n", time, )
//	pthread_mutex_destroy(philo->mutex);
//}
