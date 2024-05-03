/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:27:16 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/03 16:57:09 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int		*fork_init(int size);
static t_philo	*philosopher_init(int ac, char *av[]);

t_philo	**init_philo(int ac, char *av[])
{
	t_philo	**ret;
	t_philo	*philosopher;
	int		*right_fork;
	int		*left_fork;
	int		idx;

	idx = 0;
	ret = ft_malloc(sizeof(t_philo *) * ft_atoi(av[1]));
	right_fork = fork_init(ft_atoi(av[1]));
	left_fork = NULL;
	while (idx < ft_atoi(av[1]))
	{
		philosopher = philosopher_init(ac, av);
		philosopher->left_fork = left_fork;
		philosopher->right_fork = &(right_fork[idx]);
		philosopher->philo_num = idx + 1;
		philosopher->start_time = 0;
		philosopher->live = ALIVE;
		left_fork = &(right_fork[idx]);
		ret[idx] = philosopher;
		idx++;
	}
	ret[0]->left_fork = left_fork;
	return (ret);
}

pthread_mutex_t	*mutex_init(void)
{
	pthread_mutex_t	*mutex;

	mutex = ft_malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex, NULL);
	return (mutex);
}

static int	*fork_init(int size)
{
	int	idx;
	int	*forks;

	idx = 0;
	forks = ft_malloc(sizeof(int) * size);
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
	philosopher = ft_malloc(sizeof(t_philo));
	philosopher->die = ft_atoi(av[2]);
	philosopher->eat_time = ft_atoi(av[3]);
	philosopher->sleep_time = ft_atoi(av[4]);
	if (ac == 5)
		philosopher->eat_count = -1;
	else if (ac == 6)
		philosopher->eat_count = ft_atoi(av[5]);
	philosopher->mutex = mutex_init();
	philosopher->right_fork = &num;
	philosopher->left_fork = NULL;
	return (philosopher);
}
