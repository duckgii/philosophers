/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:23:38 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/14 21:38:34 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	end_eat(t_philo *philo, t_info *info);

void	philo_eat(t_philo *philo, t_info *info)
{
	int		check;

	check = FALSE;
	while (check == FALSE)
	{
		if (get_time(philo) - philo->start_starve > info->die_time || \
			check_info_live(info) == DIE)
			return (philo_starve(philo, info));
		if (check_all_eat(info) == TRUE)
			return ;
		check = get_first_fork(philo);
	}
	check = FALSE;
	while (check == FALSE)
	{
		if (get_time(philo) - philo->start_starve > info->die_time || \
			check_info_live(info) == DIE)
			return (philo_starve(philo, info));
		if (check_all_eat(info) == TRUE)
			return ;
		check = get_second_fork(philo);
	}
	printf("%ld %d is eating\n", get_time(philo), philo->philo_num);
	philo->start_starve = get_time(philo);
	end_eat(philo, info);
}

static void	end_eat(t_philo *philo, t_info *info)
{
	if (info->eat_time > info->die_time)
	{
		if (check_die_in_usleep(philo, info->die_time) == DIE)
			return ;
		philo_starve(philo, info);
		return ;
	}
	if (check_die_in_usleep(philo, info->eat_time) == DIE)
		return ;
	change_fork_status(philo->left_fork, UNUSED, philo->mutex_left);
	change_fork_status(philo->right_fork, UNUSED, philo->mutex_right);
	(philo->eat_count)++;
	if (philo->eat_count == info->must_eat_count)
	{
		lock(info->mutex_info);
		(info->eat_finish_count)--;
		unlock(info->mutex_info);
	}
}

void	philo_sleep(t_philo *philo, t_info *info)
{
	printf("%ld %d is sleeping\n", get_time(philo), philo->philo_num);
	if (info->eat_time + info->sleep_time > info->die_time)
	{
		if (check_die_in_usleep(philo, info->die_time - info->eat_time) == DIE)
			return ;
		philo_starve(philo, info);
		return ;
	}
	check_die_in_usleep(philo, info->sleep_time);
}

void	philo_starve(t_philo *philo, t_info *info)
{
	lock(info->mutex_info);
	if (info->live == DIE)
	{
		unlock(info->mutex_info);
		return ;
	}
	printf("%ld %d died\n", get_time(philo), philo->philo_num);
	philo->live = DIE;
	change_fork_status(philo->left_fork, UNUSED, philo->mutex_left);
	change_fork_status(philo->right_fork, UNUSED, philo->mutex_right);
	info->live = DIE;
	unlock(info->mutex_info);
}
