/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:27:16 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/06 22:20:50 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_philo	*philosopher_init(int ac, char *av[]);
static int		mutex_init(t_philo *philo);

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

static int	mutex_init(t_philo *philo)
{
	philo->mutex_philo = malloc(sizeof(pthread_mutex_t));
	if (philo->mutex_philo == NULL)
		return (FALSE);
	philo->mutex_right = malloc(sizeof(pthread_mutex_t));
	if (philo->mutex_right == NULL)
	{
		free(philo->mutex_philo);
		return (FALSE);
	}
	philo->mutex_left = malloc(sizeof(pthread_mutex_t));
	if (philo->mutex_left == NULL)
	{
		free(philo->mutex_philo);
		free(philo->mutex_right);
		return (FALSE);
	}
	pthread_mutex_init(philo->mutex_philo, NULL);
	pthread_mutex_init(philo->mutex_right, NULL);
	pthread_mutex_init(philo->mutex_left, NULL);
	return (TRUE);
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
	t_philo	*philo;
	int		num;

	num = UNUSED;
	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	if (mutex_init(philo) == FALSE)
		return (NULL);
	philo->die_time = ft_atoi(av[2]);
	philo->eat_time = ft_atoi(av[3]);
	philo->sleep_time = ft_atoi(av[4]);
	if (ac == 5)
		philo->must_eat_count = -1;
	else if (ac == 6)
		philo->must_eat_count = ft_atoi(av[5]);
	philo->start_time = 0;
	philo->live = ALIVE;
	philo->right_fork = &num;
	philo->left_fork = NULL;
	return (philo);
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
