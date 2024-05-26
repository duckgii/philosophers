/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_status_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 00:20:38 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/26 11:37:29 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	philo_starve(t_philo *philo, t_info *info)
{
	int		count;

	(void)info;
	count = 0;
	print_philo_died(philo);
	while (count < info->philo_count + 1)
	{
		sem_post(philo->all_eat);
		count--;
	}
}

void	philo_eat(t_philo *philo, t_info *info)
{
	if ((get_time(philo) - philo->start_starve) / 1000 >= info->die_time)
		philo_starve(philo, info);
	print_philo_eat(philo);
	if (info->eat_time >= info->die_time)
	{
		exact_usleep(philo, info->die_time);
		philo_starve(philo, info);
	}
	exact_usleep(philo, info->eat_time);
	sem_post(philo->fork);
	sem_post(philo->fork);
	(philo->eat_count)++;
	if (philo->eat_count == info->must_eat_count)
		sem_post(philo->all_eat);
}

void	philo_sleep(t_philo *philo, t_info *info)
{
	print_philo_sleep(philo);
	if (info->sleep_time >= info->die_time)
	{
		exact_usleep(philo, info->die_time);
		philo_starve(philo, info);
	}
	exact_usleep(philo, info->sleep_time);
}

void	philo_think(t_philo *philo)
{
	sem_wait(philo->print);
	printf("%ld %d is thinking\n", get_time(philo) / 1000, philo->philo_num);
	sem_post(philo->print);
}
