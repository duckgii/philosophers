/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_mutex_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:12:43 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/21 16:45:20 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_take_fork(t_philo *philo, t_info *info)
{
	lock(info->mutex_info[PRINT_FORK]);
	if (info->printable == PRINTABLE)
		printf("%ld %d has taken a fork\n", get_time(philo) / 1000, \
		philo->philo_num);
	unlock(info->mutex_info[PRINT_FORK]);
}

void	print_eating(t_philo *philo, t_info *info)
{
	lock(info->mutex_info[PRINT_EAT]);
	if (info->printable == PRINTABLE)
	{
		philo->start_print = get_time(philo);
		philo->start_starve = philo->start_print;
		printf("%ld %d is eating\n", philo->start_print / 1000, \
		philo->philo_num);
	}
	unlock(info->mutex_info[PRINT_EAT]);
}

void	print_sleeping(t_philo *philo, t_info *info)
{
	lock(info->mutex_info[PRINT_SLEEP]);
	if (info->printable == PRINTABLE)
	{
		philo->start_print = get_time(philo);
		printf("%ld %d is sleeping\n", philo->start_print / 1000, \
		philo->philo_num);
	}
	unlock(info->mutex_info[PRINT_SLEEP]);
}
