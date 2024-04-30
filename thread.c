/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:28:20 by yeoshin           #+#    #+#             */
/*   Updated: 2024/04/30 19:44:59 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <sys/time.h>

void		philo_eat(t_philo	*philo);
void		philo_sleep(t_philo	*philo);
static int	get_fork(int *fork, int num, t_philo *philo);
static void	start_eat(t_philo *philo);
static void	end_eat(t_philo *philo);

void	*thread_function(void *arg)
{
	t_philo			*philo;
	int				count;
	struct timeval	mytime;
	long			time;
	int				idx;

	idx = 0;
	philo = (t_philo *)arg;
	count = philo->eat_count;
	gettimeofday(&mytime, NULL);
	time = (mytime.tv_sec * 1000) + (mytime.tv_usec % 1000000) / 1000;
	philo->start_time = time;
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
	gettimeofday(&mytime, NULL);
	time = (mytime.tv_sec * 1000) + (mytime.tv_usec % 1000000) / 1000;
	printf("%ld %d died\n", time - philo->start_time, philo->philo_num);
	pthread_mutex_destroy(philo->mutex);
	return (NULL);
}

void	philo_eat(t_philo	*philo)
{
	struct timeval	mytime;
	int				check;
	long			time;

	start_eat(philo);
	check = 0;
	while (check == 0)
	{
		gettimeofday(&mytime, NULL);
		time = (mytime.tv_sec * 1000) + (mytime.tv_usec % 1000000) / 1000;
		//if (time - philo->start_starve > philo->die)
			//죽여
		if (philo->philo_num % 2 == 0)
			check = get_fork(philo->left_fork, philo->philo_num, philo);
		else
			check = get_fork(philo->right_fork, philo->philo_num, philo);
	}
	check = 0;
	while (check == 0)
	{
		gettimeofday(&mytime, NULL);
		time = (mytime.tv_sec * 1000) + (mytime.tv_usec % 1000000) / 1000;
		//if (time - philo->start_starve > philo->die)
			//죽여
		if (philo->philo_num % 2 == 0)
			check = get_fork(philo->right_fork, philo->philo_num, philo);
		else
			check = get_fork(philo->left_fork, philo->philo_num, philo);
	}
	end_eat(philo);
	pthread_mutex_unlock(philo->mutex);
}

static void	end_eat(t_philo *philo)
{
	struct timeval	mytime;
	long			time;

	gettimeofday(&mytime, NULL);
	time = (mytime.tv_sec * 1000) + (mytime.tv_usec % 1000000) / 1000;
	printf("%ld %d is eating\n", time - philo->start_time, philo->philo_num);
	usleep(philo->eat_time * 1000);
	*(philo->left_fork) = UNUSED;
	*(philo->right_fork) = UNUSED;
	gettimeofday(&mytime, NULL);
	time = (mytime.tv_sec * 1000) + (mytime.tv_usec % 1000000) / 1000;
	philo->start_starve = time;
	pthread_mutex_unlock(philo->mutex);
}

static int	get_fork(int *fork, int num, t_philo *philo)
{
	struct timeval	mytime;
	long			time;

	if (*fork == UNUSED)
	{
		gettimeofday(&mytime, NULL);
		time = (mytime.tv_sec * 1000) + (mytime.tv_usec % 1000000) / 1000;
		printf("%ld %d has taken a fork\n", time - philo->start_time, num);
		*fork = USE;
		return (1);
	}
	return (0);
}

void	philo_sleep(t_philo	*philo)
{
	struct timeval	mytime;
	long			time;

	gettimeofday(&mytime, NULL);
	time = (mytime.tv_sec * 1000) + (mytime.tv_usec % 1000000) / 1000;
	printf("%ld %d is sleeping\n", time - philo->start_time, philo->philo_num);
	if (philo->sleep_time > philo->die)
	{
		usleep(philo->die);
		//죽여
	}
	usleep(philo->sleep_time * 1000);
}

static void	start_eat(t_philo *philo)
{
	struct timeval	mytime;
	long			time;

	pthread_mutex_lock(philo->mutex);
	gettimeofday(&mytime, NULL);
	time = (mytime.tv_sec * 1000) + (mytime.tv_usec % 1000000) / 1000;
	printf("%ld %d is thinking\n", time - philo->start_time, philo->philo_num);
}
