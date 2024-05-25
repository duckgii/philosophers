/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:39:40 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/26 02:07:11 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	child_main(t_philo *philo, t_info *info)
{
	int		check_start;

	check_start = 0;
	if (philo->philo_num % 2 != 0)
		stand_by(philo, info);
	while (TRUE)
	{
		philo_wait_fork(philo, info);
		if (check_start == 0 && philo->philo_num % 2 == 0)
			sem_post(philo->start_wait);
		if (check_start == 0)
			check_start = 1;
		philo_eat(philo, info);
		philo_sleep(philo, info);
		philo_think(philo);
		usleep(100);
	}
}

static void	stand_by(t_philo *philo, t_info *info)
{
	int		count;
	int		idx;

	if (philo->philo_num == info->philo_count)
		return ;
	count = info->philo_count / 2;
	idx = 0;
	while (idx < count)
	{
		sem_wait(philo->start_wait);
		idx++;
	}
}
