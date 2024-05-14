/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_one_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:13:41 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/14 21:44:24 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	make_one_philo(t_philo *philo, t_info *info, int idx)
{
	if (idx != 0)
	{
		philo->mutex_left = info->mutex_fork[idx - 1];
		philo->left_fork = &info->fork[idx - 1];
	}
	philo->right_fork = &info->fork[idx];
	philo->mutex_right = info->mutex_fork[idx];
	philo->eat_count = 0;
	philo->start_time = 0;
	philo->start_starve = 0;
	philo->philo_num = idx + 1;
	philo->info = info;
}
