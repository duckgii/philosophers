/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:23:38 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/21 17:27:16 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philo_wait_fork(t_philo *philo, t_info *info)
{
	int		check;

	check = FALSE;
	while (check == FALSE)
	{
		if ((get_time(philo) - philo->start_starve) / 1000 >= info->die_time)
			return (philo_starve(philo, info));
		if (check_break(philo->info) == TRUE)
			return ;
		check = get_one_fork(philo, philo->right_fork, philo->mutex_right);
		if (check == FALSE)
			usleep(100);
	}
	check = FALSE;
	while (check == FALSE)
	{
		if ((get_time(philo) - philo->start_starve) / 1000 >= info->die_time)
			return (philo_starve(philo, info));
		if (check_break(philo->info) == TRUE)
			return ;
		check = get_one_fork(philo, philo->left_fork, philo->mutex_left);
		if (check == FALSE)
			usleep(100);
	}
}

void	philo_eat(t_philo *philo, t_info *info)
{
	print_eating(philo, philo->info);
	if (info->eat_time >= info->die_time)
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
		lock(info->mutex_info[MUTEX_ALL_EAT]);
		(info->eat_finish_count)--;
		unlock(info->mutex_info[MUTEX_ALL_EAT]);
	}
}

void	philo_sleep(t_philo *philo, t_info *info)
{
	print_sleeping(philo, philo->info);
	if (info->eat_time + info->sleep_time >= info->die_time)
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
	lock(info->mutex_info[PRINT_DIE]);
	if (info->printable == PRINTABLE)
	{
		lock(info->mutex_info[PRINT_THINK]);
		lock(info->mutex_info[PRINT_FORK]);
		lock(info->mutex_info[PRINT_EAT]);
		lock(info->mutex_info[PRINT_SLEEP]);
		printf("%ld %d died\n", get_time(philo) / 1000, philo->philo_num);
		info->printable = NOT_PRINTABLE;
		unlock(info->mutex_info[PRINT_DIE]);
		unlock(info->mutex_info[PRINT_SLEEP]);
		unlock(info->mutex_info[PRINT_EAT]);
		unlock(info->mutex_info[PRINT_FORK]);
		unlock(info->mutex_info[PRINT_THINK]);
		lock(info->mutex_info[MUTEX_LIVE]);
		info->live = DIE;
		unlock(info->mutex_info[MUTEX_LIVE]);
	}
	else
		unlock(info->mutex_info[PRINT_DIE]);
}

void	philo_think(t_philo *philo, t_info *info)
{
	lock(info->mutex_info[PRINT_THINK]);
	if (info->printable == PRINTABLE)
		printf("%ld %d is thinking\n", get_time(philo) / 1000, philo->philo_num);
	unlock(info->mutex_info[PRINT_THINK]);
	return ;
}
