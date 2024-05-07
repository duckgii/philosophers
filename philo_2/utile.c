/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:49:51 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/07 14:11:52 by yeoshin          ###   ########.fr       */
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

int	check_die_in_usleep(t_main *main, int time)
{
	int		idx;

	while (idx < 20)
	{
		idx++;
		if (check_main_die(main) == DIE)
			return (philo_die(main->philo));
		usleep((time / 20) * 1000);
	}
	if (check_main_die(main) == DIE)
		return (philo_die(main->philo));
	return (ALIVE);
}

void	check_and_change_die(t_philo *philo)
{
	if (philo->live == DIE)
		return ;
	philo->live = DIE;
	printf("%ld %d is died\n", get_time(philo), philo->philo_num);
}
