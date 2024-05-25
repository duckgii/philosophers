/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:26:56 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/25 21:11:09 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void		make_one_philo(t_philo *philo, int count);
static t_info	*init_info(int ac, char *av[]);

t_philo	*parse_philo(int ac, char *av[])
{
	t_philo	*ret;
	int		count;
	t_info	*info;

	count = ft_atoi(av[1]);
	ret = ft_malloc(sizeof(t_philo *) * count);
	make_one_philo(ret, count);
	return (ret);
}

static void	make_one_philo(t_philo *philo, int count)
{
	philo->eat_count = 0;
	philo->start_time = 0;
	philo->start_starve = 0;
	philo->start_print = 0;
	philo->philo_num = 0;
	philo->fork = ft_malloc(sizeof(sem_t));
	philo->fork = sem_open("fork", O_CREAT, 0600, count);
	philo->print = ft_malloc(sizeof(sem_t));
	philo->print = sem_open("print", O_CREAT, 0600, count);
	philo->all_eat = ft_malloc(sizeof(sem_t));
	philo->all_eat = sem_open("print", O_CREAT, 0600, 0);
	philo->start_wait = ft_malloc(sizeof(sem_t));
	philo->start_wait = sem_open("start_wait", O_CREAT, 0600, 0);
}

t_info	*init_info(int ac, char *av[])
{
	t_info	*info;

	info = ft_malloc(sizeof(t_info));
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	info->philo_count = ft_atoi(av[1]);
	info->eat_finish_count = ft_atoi(av[1]);
	info->live = ALIVE;
	info->printable = PRINTABLE;
	info->get_fork_count = ft_atoi(av[1]) / 2;
	if (ac == 5)
		info->must_eat_count = -1;
	else if (ac == 6)
		info->must_eat_count = ft_atoi(av[5]);
	return (info);
}
