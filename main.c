/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:21:57 by yeoshin           #+#    #+#             */
/*   Updated: 2024/04/29 12:27:57 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	thread_start(t_philo **philo, pthread_t *threads, int count);
static int	thread_end(pthread_t *threads, int count);

int	main(int ac, char *av[])
{
	t_philo			**philo;
	pthread_t		*threads;
	pthread_mutex_t	*mutex;
	int				ret;

	if (ac != 6)
		return (1);
	mutex = mutex_init();
	philo = init_philo(av, mutex);
	threads = ft_malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	if (thread_start(philo, threads, ft_atoi(av[1])));
		return (1);
	ret = thread_end(threads, ft_atoi(av[1]));
	if (thread_end(threads, ft_atoi(av[1])))
		return (1);
	return (0);
}

static int	thread_start(t_philo **philo, pthread_t *threads, int count)
{
	int	idx;
	int	res;

	idx = 0;
	while (idx < count)
	{
		res = pthread_create(&threads[idx], NULL, thread_function, philo[idx]);
		if (res != 0)
		{
			printf("main thread is failed");
			return (1);
		}
		idx++;
	}
	return (0);
}

static int	thread_end(pthread_t *threads, int count)
{
	int			idx;
	int			res;

	idx = 0;
	while (idx < count)
	{
		res = pthread_join(threads[idx], NULL);
		if (res != 0)
		{
			printf("main thread is failed");
			return (0);
		}
		idx++;
	}
	return (1);
}
