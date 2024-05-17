/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_mutex_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:12:43 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/17 15:32:17 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_take_fork(t_philo *philo, t_info *info)
{
	lock(info->mutex_live);
	if (info->live == ALIVE)
		printf("%ld %d has taken a fork\n", get_time(philo), philo->philo_num);
	unlock(info->mutex_live);
}

void	print_eating(t_philo *philo, t_info *info)
{
	lock(info->mutex_live);
	if (info->live == ALIVE)
		printf("%ld %d is eating\n", get_time(philo), philo->philo_num);
	unlock(info->mutex_live);
}

void	print_sleeping(t_philo *philo, t_info *info)
{
	lock(info->mutex_printable);
	if (info->live == ALIVE)
		printf("%ld %d is sleeping\n", get_time(philo), philo->philo_num);
	unlock(info->mutex_printable);
}
