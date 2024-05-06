/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:21:57 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/06 20:23:44 by yeoshin          ###   ########.fr       */
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
	int			*fork;

	fork = fork_init(ft_atoi(av[1]));
	if (fork == NULL)
		return (NULL);
	philo = init_philo(ac, av, fork);
	if (philo == NULL)
		return (free_fork(fork));
	monitor = init_monitor(philo, ft_atoi(av[1]));
	if (monitor == NULL)
		return (free_philo_fork(philo, ft_atoi(av[1]), fork));
	threads = malloc(sizeof(pthread_t) * (ft_atoi(av[1]) + 1));
	if (threads == NULL)
		return (free_philo_monitor_fork(philo, monitor, ft_atoi(av[1]), fork));
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
			printf("main thread is failed\n");
			return (1);
		}
		idx++;
	}
	res = pthread_create(&threads[idx], NULL, monitoring_thread, monitor);
	if (res != 0)
	{
		printf("main thread is failed\n");
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
			printf("main thread is failed\n");
			return (1);
		}
		idx++;
	}
	return (0);
}
