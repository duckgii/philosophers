/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:28:20 by yeoshin           #+#    #+#             */
/*   Updated: 2024/04/30 11:44:49 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <sys/time.h>
void	get_fork(t_philo	*philo);
void	get_sleep(t_philo	*philo);

void	*thread_function(void *arg)
{
	t_philo		*philo;
	int			count = 0;
	struct timeval	mytime;
	//int			i=0;

	//pthread_mutex_lock(philo->mutex);
	//while (i < 6)
	//{
	//	printf("i : %d\n", i);
	//	i++;
	//}
	//pthread_mutex_unlock(philo->mutex);
	//printf("philosopher right fork is %d\n", *philo->right_fork);
	//printf("philosopher left fork is %d\n", *philo->left_fork);
	//gettimeofday(&mytime, NULL);
	//printf("now : %d = %d\n", philo->philo_num, mytime.tv_usec);
	//usleep(100);
	//gettimeofday(&mytime, NULL);
	//printf("after : %d = %d\n", philo->philo_num, mytime.tv_usec);
	philo = (t_philo *)arg;
	while (count < 5)
	{
		get_fork(philo);
		get_sleep(philo);
		printf("\nphilo_num : %d->%d\n\n", philo->philo_num, count + 1);
		count++;
	}
	//gettimeofday(&mytime, NULL);
	//printf("philo %d start!!%d\n", philo->philo_num, mytime.tv_usec);
	//usleep(200);
	//gettimeofday(&mytime, NULL);
	//printf("philo %d end!!%d\n", philo->philo_num, mytime.tv_usec);
	return (NULL);
}

void	get_fork(t_philo	*philo)
{
	struct timeval	mytime;

	pthread_mutex_lock(philo->mutex);
	gettimeofday(&mytime, NULL);
	printf("philo %d think!!%d\n", philo->philo_num, mytime.tv_usec);
	while (1)
	{
		if (*(philo->left_fork) == HAVE)
		{
			*(philo->left_fork) = EMPTY;
			printf("philo %d left_fork!\n", philo->philo_num);
			break ;
		}
	}
	while (1)
	{
		if (*(philo->right_fork) == HAVE)
		{
			*(philo->right_fork) = EMPTY;
			printf("philo %d right_fork!\n", philo->philo_num);
			break ;
		}
	}
	gettimeofday(&mytime, NULL);
	printf("philo %d start_eat!!%d\n", philo->philo_num, mytime.tv_usec);
	usleep(100);
	gettimeofday(&mytime, NULL);
	printf("philo %d end_eat!!%d\n", philo->philo_num, mytime.tv_usec);
	*(philo->left_fork) = HAVE;
	*(philo->right_fork) = HAVE;
	pthread_mutex_unlock(philo->mutex);
}

void	get_sleep(t_philo	*philo)
{
	printf("philo %d sleep!!\n", philo->philo_num);
	usleep(50);
}
