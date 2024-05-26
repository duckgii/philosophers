/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:39:40 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/26 13:46:28 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void	stand_by(t_philo *philo, t_info *info);
static void	exact_first_usleep(t_philo *philo, long time);

void	child_main(t_philo *philo, t_info *info)
{
	int		check_start;

	check_start = 0;
	sem_wait(philo->start_wait);
	exact_first_usleep(philo, philo->adjust_time);
	philo->start_time += philo->adjust_time;
	if (philo->philo_num % 2 != 0 && philo->philo_num != info->philo_count)
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
	exit(0);
}

static void	stand_by(t_philo *philo, t_info *info)
{
	int		count;
	int		idx;

	if (philo->philo_num == info->philo_count)
	{
		usleep(500);
		return ;
	}
	count = info->philo_count / 2;
	idx = 0;
	sem_wait(philo->start_wait);
	usleep(info->eat_time * 500);
}

static void	exact_first_usleep(t_philo *philo, long time)
{
	time -= get_time(philo);
	usleep(time * (0.8));
	while (TRUE)
	{
		if (time <= get_time(philo) - philo->start_print)
			break ;
		usleep(100);
	}
}
