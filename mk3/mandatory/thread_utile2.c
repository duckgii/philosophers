/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utile2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:44:11 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/21 17:26:43 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_info_live(t_info *info)
{
	lock(info->mutex_info[MUTEX_LIVE]);
	if (info->live == DIE)
	{
		unlock(info->mutex_info[MUTEX_LIVE]);
		return (DIE);
	}
	unlock(info->mutex_info[MUTEX_LIVE]);
	return (ALIVE);
}

int	check_all_eat(t_info *info)
{
	lock(info->mutex_info[MUTEX_ALL_EAT]);
	if (info->eat_finish_count == 0)
	{
		lock(info->mutex_info[PRINT_THINK]);
		lock(info->mutex_info[PRINT_FORK]);
		lock(info->mutex_info[PRINT_EAT]);
		lock(info->mutex_info[PRINT_SLEEP]);
		lock(info->mutex_info[PRINT_DIE]);
		info->printable = NOT_PRINTABLE;
		unlock(info->mutex_info[PRINT_DIE]);
		unlock(info->mutex_info[PRINT_SLEEP]);
		unlock(info->mutex_info[PRINT_EAT]);
		unlock(info->mutex_info[PRINT_FORK]);
		unlock(info->mutex_info[PRINT_THINK]);
		unlock(info->mutex_info[MUTEX_ALL_EAT]);
		return (TRUE);
	}
	unlock(info->mutex_info[MUTEX_ALL_EAT]);
	return (FALSE);
}

int	check_die_in_usleep(t_philo *philo, long time)
{
	t_info	*info;

	info = philo->info;
	if (check_break(philo->info) == TRUE)
		return (DIE);
	usleep(time * 800);
	time = time * 1000;
	while (TRUE)
	{
		if (time <= get_time(philo) - philo->start_print)
			break ;
		if (check_break(philo->info) == TRUE)
			break ;
		usleep(100);
	}
	if (check_break(philo->info) == TRUE)
		return (DIE);
	return (ALIVE);
}

int	check_break(t_info *info)
{
	if (check_all_eat(info) == TRUE || check_info_live(info) == DIE)
		return (TRUE);
	return (FALSE);
}
