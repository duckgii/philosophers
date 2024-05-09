/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:36:58 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/09 16:59:14 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_philo	*set_philo(int *fork, pthread_mutex_t **mutex, \
					int idx, t_philo **all_philo);

int	*init_fork(int count)
{
	int		idx;
	int		*fork;

	idx = 0;
	fork = malloc(sizeof(int) * count);
	if (fork == NULL)
		return (NULL);
	while (idx < count)
	{
		fork[idx] = UNUSED;
		idx++;
	}
	return (fork);
}

t_info	*init_info(int ac, char *av[])
{
	t_info			*info;
	pthread_mutex_t	*mutex_info;

	info = malloc(sizeof(t_info));
	if (info == NULL)
		return (NULL);
	mutex_info = malloc(sizeof(pthread_mutex_t));
	if (mutex_info == NULL)
		return (free_one(info));
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	info->philo_count = ft_atoi(av[1]);
	info->mutex_fork = init_fork_mutex(ft_atoi(av[1]));
	info->eat_finish = ft_atoi(av[1]);
	info->live = ALIVE;
	if (ac == 5)
		info->must_eat_count = -1;
	else if (ac == 6)
		info->must_eat_count = ft_atoi(av[5]);
	pthread_mutex_init(mutex_info, NULL);
	info->mutex_info = mutex_info;
	return (info);
}

t_philo	**init_philo(int *fork, int count, t_info *info)
{
	t_philo			**philo;
	int				idx;

	idx = 0;
	philo = malloc(sizeof(t_philo *) * count);
	if (philo == NULL)
		return (NULL);
	while (idx < count)
	{
		philo[idx] = set_philo(fork, info->mutex_fork, idx, philo);
		if (philo[idx] == NULL)
			return (free_philo(philo, idx));
		philo[idx]->info = info;
		idx++;
	}
	init_first_philo(philo, count);
	return (philo);
}

static t_philo	*set_philo(int *fork, pthread_mutex_t **mutex, \
					int idx, t_philo **all_philo)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	if (idx != 0)
	{
		philo->mutex_left = all_philo[idx - 1]->mutex_right;
		philo->left_fork = all_philo[idx - 1]->right_fork;
	}
	philo->right_fork = &fork[idx];
	philo->mutex_right = mutex[idx];
	philo->live = ALIVE;
	philo->eat_count = 0;
	philo->start_time = 0;
	philo->start_starve = 0;
	philo->philo_num = idx + 1;
	return (philo);
}

void	init_first_philo(t_philo **philo, int count)
{
	philo[0]->mutex_left = philo[count - 1]->mutex_right;
	if (count == 1)
		*(philo[0]->left_fork) = USE;
	else
		philo[0]->left_fork = philo[count - 1]->right_fork;
}
