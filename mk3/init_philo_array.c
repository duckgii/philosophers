/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:27:50 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/17 15:03:55 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_philo		**malloc_philo(int count);
static t_philo		**init_philo_array(t_philo **philo, int ac, char **av);
static void			init_first_philo(t_philo **philo, int count);
static t_info		*init_info(int ac, char *av[]);

t_philo	**parse_arg(int ac, char *av[])
{
	t_philo	**ret;

	ret = malloc_philo(ft_atoi(av[1]));
	if (ret == NULL)
		return (NULL);
	ret = init_philo_array(ret, ac, av);
	return (ret);
}

static t_philo	**malloc_philo(int count)
{
	t_philo	**ret;
	int		idx;

	idx = 0;
	ret = malloc(sizeof(t_philo *) * count);
	if (ret == NULL)
		return (NULL);
	while (idx < count)
	{
		ret[idx] = malloc(sizeof(t_philo));
		if (ret[idx] == NULL)
			return (free_malloc_philos(ret, idx));
		idx++;
	}
	return (ret);
}

static t_philo	**init_philo_array(t_philo **philo, int ac, char **av)
{
	int		idx;
	t_info	*info;

	idx = 0;
	info = init_info(ac, av);
	if (info == NULL)
		return (free_malloc_philos(philo, ft_atoi(av[1])));
	while (idx < ft_atoi(av[1]))
	{
		make_one_philo(philo[idx], info, idx);
		idx++;
	}
	init_first_philo(philo, ft_atoi(av[1]));
	return (philo);
}

static t_info	*init_info(int ac, char *av[])
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (info == NULL)
		return (NULL);
	if (malloc_info(info, av) == NULL)
		return (free_one(info));
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	info->philo_count = ft_atoi(av[1]);
	info->eat_finish_count = ft_atoi(av[1]);
	info->live = ALIVE;
	info->printable = PRINTABLE;
	if (ac == 5)
		info->must_eat_count = -1;
	else if (ac == 6)
		info->must_eat_count = ft_atoi(av[5]);
	return (info);
}

static void	init_first_philo(t_philo **philo, int count)
{
	if (count == 1)
	{
		philo[0]->mutex_left = NULL;
		philo[0]->left_fork = NULL;
		return ;
	}
	philo[0]->left_fork = philo[count - 1]->right_fork;
	philo[0]->mutex_left = philo[count - 1]->mutex_right;
}
