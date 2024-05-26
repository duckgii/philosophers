/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utile_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:44:26 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/26 16:13:43 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	philo_wait_fork(t_philo *philo, t_info *info)
{
	int		count;

	count = 0;
	while (count < 2)
	{
		if (count == 1 && info->philo_count == 1)
		{
			exact_usleep(philo, info->die_time);
			philo_starve(philo, info);
		}
		sem_wait(philo->fork);
		print_get_fork(philo);
		usleep(100);
		count++;
	}
}

void	exact_usleep(t_philo *philo, int time)
{
	usleep(time * 800);
	time = time * 1000;
	while (TRUE)
	{
		if (time <= get_time(philo) - philo->start_print)
			break ;
		usleep(100);
	}
}
