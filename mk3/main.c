/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:42:53 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/15 17:58:57 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int			start_threads(t_philo **philo, pthread_t **threads);
static int			end_threads(pthread_t **threads, int philo_count);
static pthread_t	**init_threads(int count);

int	main(int ac, char *av[])
{
	t_philo		**philo;
	pthread_t	**threads;

	//if (check_arg(ac, av) == FALSE)
	//	return (1);
	philo = parse_arg(ac, av);
	if (philo == NULL)
		return (1);
	threads = init_threads(ft_atoi(av[1]));
	if (threads == NULL)
		return (free_philo(philo));
	if (start_threads(philo, threads) != 0)
		return (free_philo_threads(philo, threads));
	if (end_threads(threads, ft_atoi(av[1])) != 0)
		return (free_philo_threads(philo, threads));
	return (0);
}

static int	start_threads(t_philo **philo, pthread_t **threads)
{
	int				idx;
	int				ret;
	long			time;
	struct timeval	mytime;

	idx = 0;
	lock(philo[0]->info->mutex_live);
	while (idx < philo[0]->info->philo_count)
	{
		ret = pthread_create(threads[idx], NULL, thread_function, philo[idx]);
		if (ret != 0)
		{
			printf("info thread is failed\n");
			end_threads(threads, idx);
			return (1);
		}
		idx++;
	}
	gettimeofday(&mytime, NULL);
	time = (mytime.tv_sec * 1000) + mytime.tv_usec / 1000;
	philo[0]->info->start_time = time;
	unlock(philo[0]->info->mutex_live);
	return (0);
}

static int	end_threads(pthread_t **threads, int philo_count)
{
	int			idx;
	int			ret;
	int			check;

	idx = 0;
	check = 0;
	ret = 0;
	while (idx < philo_count)
	{
		check = pthread_join(*threads[idx], NULL);
		if (check != 0)
		{
			printf("info thread is failed\n");
			ret = 1;
		}
		idx++;
	}
	return (ret);
}

static pthread_t	**init_threads(int count)
{
	pthread_t	**ret;
	int			idx;

	idx = 0;
	ret = malloc(sizeof(pthread_t *) * count);
	if (ret == NULL)
		return (NULL);
	while (idx < count)
	{
		ret[idx] = malloc(sizeof(pthread_t));
		if (ret[idx] == NULL)
			return (free_malloc_threads(ret, idx));
		idx++;
	}
	return (ret);
}

//static int check_arg(int ac, char *av[])
//{}