/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:27:16 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/06 20:24:12 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_philo	*philosopher_init(int ac, char *av[]);

t_philo	**init_philo(int ac, char *av[], int *fork)
{
	t_philo	**ret;
	t_philo	*philosopher;
	int		*right_fork;
	int		*left_fork;
	int		idx;

	idx = 0;
	ret = malloc(sizeof(t_philo *) * ft_atoi(av[1]));
	if (ret == NULL)
		return (NULL);
	while (idx < ft_atoi(av[1]))
	{
		philosopher = philosopher_init(ac, av);
		if (philosopher == NULL)
			return (free_philo(ret, ft_atoi(av[1])));
		philosopher->left_fork = left_fork;
		philosopher->right_fork = &(fork[idx]);
		philosopher->philo_num = idx + 1;
		left_fork = &(fork[idx]);
		ret[idx] = philosopher;
		idx++;
	}
	ret[0]->left_fork = left_fork;
	return (ret);
}

pthread_mutex_t	*mutex_init(void)
{
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t));
	if (mutex == NULL)
		return (NULL);
	pthread_mutex_init(mutex, NULL);
	return (mutex);
}

int	*fork_init(int size)
{
	int	idx;
	int	*forks;

	idx = 0;
	forks = malloc(sizeof(int) * size);
	if (forks == NULL)
		return (NULL);
	while (idx < size)
	{
		forks[idx] = UNUSED;
		idx++;
	}
	return (forks);
}

static t_philo	*philosopher_init(int ac, char *av[])
{
	t_philo	*philosopher;
	int		num;

	num = UNUSED;
	philosopher = malloc(sizeof(t_philo));
	if (philosopher == NULL)
		return (NULL);
	philosopher->die_time = ft_atoi(av[2]);
	philosopher->eat_time = ft_atoi(av[3]);
	philosopher->sleep_time = ft_atoi(av[4]);
	if (ac == 5)
		philosopher->must_eat_count = -1;
	else if (ac == 6)
		philosopher->must_eat_count = ft_atoi(av[5]);
	philosopher->mutex = mutex_init();
	if (philosopher->mutex == NULL)
		return (NULL);
	philosopher->start_time = 0;
	philosopher->live = ALIVE;
	philosopher->right_fork = &num;
	philosopher->left_fork = NULL;
	return (philosopher);
}

t_monitor	*init_monitor(t_philo **philo, int philo_count)
{
	t_monitor	*monitor;

	monitor = malloc(sizeof(t_monitor));
	if (monitor == NULL)
		return (NULL);
	monitor->philo = philo;
	monitor->philo_count = philo_count;
	return (monitor);
}
