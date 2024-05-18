/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utile2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:44:11 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/18 10:43:37 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_info_live(t_info *info)
{
	lock(info->mutex_live);
	if (info->live == DIE)
	{
		unlock(info->mutex_live);
		return (DIE);
	}
	unlock(info->mutex_live);
	return (ALIVE);
}

int	check_all_eat(t_info *info)
{
	lock(info->mutex_all_eat);
	if (info->eat_finish_count == 0)
	{
		lock(info->mutex_printable);
		info->printable = NOT_PRINTABLE;
		unlock(info->mutex_printable);
		unlock(info->mutex_all_eat);
		return (TRUE);
	}
	unlock(info->mutex_all_eat);
	return (FALSE);
}

int	check_die_in_usleep(t_philo *philo, long time)
{
	t_info	*info;
	long	start_time;

	info = philo->info;
	start_time = get_time(philo);
	if (check_break(philo->info) == TRUE)
		return (DIE);
	usleep(time * 800);
	while (TRUE)
	{
		if (philo->info->eat_time == get_time(philo) - start_time)
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
