/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:26:56 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/26 11:21:54 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void		make_one_philo(t_philo *philo, int count);

t_philo	*parse_philo(char *av[])
{
	t_philo	*ret;
	int		count;

	count = ft_atoi(av[1]);
	ret = ft_malloc(sizeof(t_philo));
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
	sem_unlink("all_eat");
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("start_wait");
	philo->fork = sem_open("fork", O_CREAT, 0777, count);
	philo->print = sem_open("print", O_CREAT, 0777, 1);
	philo->all_eat = sem_open("all_eat", O_CREAT, 0777, 0);
	philo->start_wait = sem_open("start_wait", O_CREAT, 0777, 0);
	if (philo->fork == SEM_FAILED || philo->print == SEM_FAILED || \
	philo->all_eat == SEM_FAILED || philo->start_wait == SEM_FAILED)
	{
		perror("sem_open error");
		exit(1);
	}
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
	if (ac == 5)
		info->must_eat_count = -1;
	else if (ac == 6)
		info->must_eat_count = ft_atoi(av[5]);
	return (info);
}
