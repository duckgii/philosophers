/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:21:57 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/03 22:30:18 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	thread_start(t_philo **philo, \
						pthread_t *threads, t_monitor *monitor);
static int	thread_end(pthread_t *threads, t_monitor *monitor);

int	main(int ac, char *av[])
{
	t_philo		**philo;
	pthread_t	*threads;
	t_monitor	*monitor;
	int			ret;

	philo = init_philo(ac, av);
	monitor = init_monitor(philo, ft_atoi(av[1]));
	threads = ft_malloc(sizeof(pthread_t) * (ft_atoi(av[1]) + 1));
	if (thread_start(philo, threads, monitor))
		return (1);
	if (thread_end(threads, monitor))
		return (1);
	return (0);
}

static int	thread_start(t_philo **philo,
						pthread_t *threads, t_monitor *monitor)
{
	int			idx;
	int			res;

	idx = 0;
	while (idx < monitor->philo_count)
	{
		res = pthread_create(&threads[idx], NULL, thread_function, philo[idx]);
		if (res != 0)
		{
			printf("main thread is failed1\n");
			return (1);
		}
		idx++;
	}
	res = pthread_create(&threads[idx], NULL, monitoring_thread, monitor);
	if (res != 0)
	{
		printf("main thread is failed1\n");
		return (1);
	}
	return (0);
}

static int	thread_end(pthread_t *threads, t_monitor *monitor)
{
	int			idx;
	int			res;

	idx = 0;
	res = 0;
	while (idx < monitor->philo_count + 1)
	{
		res = pthread_join(threads[idx], NULL);
		if (res != 0)
		{
			printf("main thread is failed2\n");
			return (1);
		}
		idx++;
	}
	return (0);
}
