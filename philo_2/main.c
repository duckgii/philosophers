/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:18:00 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/09 17:00:08 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	thread_start(pthread_t *threads, t_info *info, t_philo **philo);
static int	thread_end(pthread_t *threads, int philo_count);

int	main(int ac, char *av[])
{
	t_info		*info;
	int			*fork;
	pthread_t	*threads;
	t_philo		**philo;

	fork = init_fork(ft_atoi(av[1]));
	if (fork == NULL)
		return (1);
	info = init_info(ac, av);
	if (info == NULL)
		return (free_fork(fork));
	philo = init_philo(fork, ft_atoi(av[1]), info);
	if (philo == NULL)
		return (free_fork_info(fork, info));
	threads = init_threads(ft_atoi(av[1]));
	if (threads == NULL)
		return (free_fork_info_philo(fork, info, philo));
	if (thread_start(threads, info, philo))
		return (free_fork_info_philo_threads(fork, info, philo, threads));
	if (thread_end(threads, info->philo_count))
		return (free_fork_info_philo_threads(fork, info, philo, threads));
	free_fork_info_philo_threads(fork, info, philo, threads);
	return (0);
}

static int	thread_start(pthread_t *threads, t_info *info, t_philo **philo)
{
	int		idx;
	int		ret;

	idx = 0;
	while (idx < info->philo_count)
	{
		ret = pthread_create(&threads[idx], NULL, thread_function, philo[idx]);
		if (ret != 0)
		{
			printf("info thread is failed\n");
			return (1);
		}
		idx++;
	}
	return (0);
}

static int	thread_end(pthread_t *threads, int philo_count)
{
	int			idx;
	int			ret;

	idx = 0;
	ret = 0;
	while (idx < philo_count)
	{
		ret = pthread_join(threads[idx], NULL);
		if (ret != 0)
		{
			printf("info thread is failed\n");
			return (1);
		}
		idx++;
	}
	return (0);
}
