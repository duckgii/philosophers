/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:22:52 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/03 16:55:23 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	philo_eat(t_philo	*philo);
void		philo_sleep(t_philo	*philo);

void	*thread_function(void *arg)
{
	t_philo			*philo;
	int				count;
	long			time;
	int				idx;

	idx = 0;
	philo = (t_philo *)arg;
	count = philo->eat_count;
	philo->start_time = get_time(philo);
	start_philo(philo);
	time = get_time(philo);
	printf("%ld %d died\n", time, philo->philo_num);
	pthread_mutex_destroy(philo->mutex);
	return (NULL);
}

void	start_philo(t_philo *philo)
{
	int		idx;
	int		count;

	idx = 0;
	count = philo->eat_count;
	if (count == -1)
	{
		while (1)
		{
			philo_eat(philo);
			philo_sleep(philo);
		}
	}
	else
	{
		while (idx < count)
		{
			philo_eat(philo);
			philo_sleep(philo);
			idx++;
		}
	}
	return ;
}

static void	philo_eat(t_philo	*philo)
{
	int				check;
	long			time;

	mutex_lock_and_think(philo);
	check = 0;
	while (check == 0)
	{
		time = get_time(philo);
		//if (time - philo->start_starve > philo->die)
			//죽여 
		check = get_fork(FIRST_EAT, philo);
	}
	check = 0;
	while (check == 0)
	{
		time = get_time(philo);
		//if (time - philo->start_starve > philo->die)
			//죽여
		check = get_fork(SECOND_EAT, philo);
	}
	end_eat(philo);
	pthread_mutex_unlock(philo->mutex);
}

void	philo_sleep(t_philo	*philo)
{
	struct timeval	mytime;
	long			time;

	time = get_time(philo);
	printf("%ld %d is sleeping\n", time, philo->philo_num);
	if (philo->sleep_time > philo->die)
	{
		usleep(philo->die);
		//죽여
	}
	usleep(philo->sleep_time * 1000);
}

//void	phlio_die(t_philo *phlio, long time)
//{

//}
