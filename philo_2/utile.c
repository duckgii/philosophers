/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:49:51 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/09 17:06:38 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	get_time(t_philo *philo)
{
	struct timeval	mytime;
	long			time;

	gettimeofday(&mytime, NULL);
	time = (mytime.tv_sec * 1000) + mytime.tv_usec / 1000;
	return (time - philo->start_time);
}

int	philo_die(t_philo *philo)
{
	philo->live = DIE;
	printf("%ld %d id died\n", get_time(philo), philo->philo_num);
	change_fork_status(philo->left_fork, UNUSED, philo->mutex_left);
	change_fork_status(philo->right_fork, UNUSED, philo->mutex_right);
	return (DIE);
}

int	check_die_in_usleep(t_philo *philo, int time)
{
	int		idx;

	idx = 0;
	while (idx < 20)
	{
		idx++;
		if (check_info_die(philo->info) == DIE)
			return (philo_die(philo));
		usleep((time / 20) * 1000);
	}
	if (check_info_die(philo->info) == DIE)
		return (philo_die(philo));
	return (ALIVE);
}

void	check_and_change_die(t_philo *philo)
{
	t_info	*info;

	if (philo->live == DIE)
		return ;
	philo->live = DIE;
	printf("%ld %d is died\n", get_time(philo), philo->philo_num);
	info = philo->info;
	lock(info->mutex_info);
	info->live = DIE;
	unlock(info->mutex_info);
}
