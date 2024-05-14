/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:04:08 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/14 21:39:04 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*thread_function(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	philo->start_time = get_time(philo);
	philo->start_starve = philo->start_time;
	while (1)
	{
		printf("%ld %d is thinking\n", get_time(philo), philo->philo_num);
		philo_eat(philo, info);
		if (check_all_eat(info) == TRUE || philo->live == DIE || \
			check_someone_die(info) == TRUE)
			break ;
		philo_sleep(philo, info);
		if (check_all_eat(info) == TRUE || philo->live == DIE || \
			check_someone_die(info) == TRUE)
			break ;
	}
	return (NULL);
}

int	check_all_eat(t_info *info)
{
	lock(info->mutex_info);
	if (info->eat_finish_count == 0)
	{
		unlock(info->mutex_info);
		return (TRUE);
	}
	unlock(info->mutex_info);
	return (FALSE);
}

int	check_someone_die(t_info *info)
{
	lock(info->mutex_info);
	if (info->live == DIE)
	{
		unlock(info->mutex_info);
		return (TRUE);
	}
	unlock(info->mutex_info);
	return (FALSE);
}
