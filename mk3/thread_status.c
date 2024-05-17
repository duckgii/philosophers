/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:23:38 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/17 15:32:03 by yeoshin          ###   ########.fr       */
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
		if (get_time(philo) - philo->start_starve > info->die_time)
			return (philo_starve(philo, info));
		if (check_all_eat(info) == TRUE || check_info_live(info) == DIE)
			return ;
		check = get_first_fork(philo);
		usleep(100);
	}
	check = FALSE;
	while (check == FALSE)
	{
		if (get_time(philo) - philo->start_starve > info->die_time)
			return (philo_starve(philo, info));
		if (check_all_eat(info) == TRUE || check_info_live(info) == DIE)
			return ;
		check = get_second_fork(philo);
		usleep(100);
	}
	end_eat(philo, info);
}

static void	end_eat(t_philo *philo, t_info *info)
{
	print_eating(philo, philo->info);
	philo->start_starve = get_time(philo);
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
		lock(info->mutex_live);
		(info->eat_finish_count)--;
		unlock(info->mutex_live);
	}
}

void	philo_sleep(t_philo *philo, t_info *info)
{
	print_sleeping(philo, philo->info);
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
	if (philo->mutex_left != NULL)
		change_fork_status(philo->left_fork, UNUSED, philo->mutex_left);
	if (philo->mutex_right != NULL)
		change_fork_status(philo->right_fork, UNUSED, philo->mutex_right);
	lock(info->mutex_printable);
	if (info->printable == PRINTABLE)
	{
		printf("%ld %d died\n", get_time(philo), philo->philo_num);
		info->printable = NOT_PRINTABLE;
		lock(info->mutex_live);
		info->live = DIE;
		unlock(info->mutex_live);
	}
	unlock(info->mutex_printable);
}

int	philo_think(t_philo *philo, t_info *info)
{
	lock(info->mutex_printable);
	if (info->printable == PRINTABLE)
	{
		printf("%ld %d is thinking\n", get_time(philo), philo->philo_num);
		unlock(info->mutex_printable);
		return (ALIVE);
	}
	unlock(info->mutex_printable);
	return (DIE);
}
