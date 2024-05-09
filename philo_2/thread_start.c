/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:41:48 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/09 16:59:30 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	end_eat(t_philo *philo);
static void	philo_eat(t_philo *philo);
static void	philo_sleep(t_philo *philo);

void	*thread_function(void *arg)
{
	t_info	*info;
	t_philo	*philo;

	philo = (t_philo *)arg;
	info = philo->info;
	philo->start_time = get_time(philo);
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		lock(info->mutex_info);
		check_all_eat(info, philo);
		if (info->live == DIE)
		{
			unlock(info->mutex_info);
			check_and_change_die(philo);
			break ;
		}
		unlock(info->mutex_info);
	}
	return (NULL);
}

static void	philo_eat(t_philo *philo)
{
	int		check;
	t_info	*info;

	check = FALSE;
	info = philo->info;
	printf("%ld %d is thinking\n", get_time(philo), philo->philo_num);
	while (check == FALSE)
	{
		if (philo->live == DIE)
			return ;
		if (get_time(philo) - philo->start_starve > info->die_time)
			return (philo_starve(philo));
		check = get_first_fork(philo);
	}
	check = FALSE;
	while (check == FALSE)
	{
		if (get_time(philo) - philo->start_starve > info->die_time)
			return (philo_starve(philo));
		check = get_second_fork(philo);
	}
	printf("%ld %d is eating\n", get_time(philo), philo->philo_num);
	end_eat(philo);
}

void	philo_starve(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	if (philo->live == DIE)
		return ;
	philo->live = DIE;
	lock(info->mutex_info);
	info->live = DIE;
	unlock(info->mutex_info);
	printf("%ld %d died\n", get_time(philo), philo->philo_num);
	change_fork_status(philo->left_fork, UNUSED, philo->mutex_left);
	change_fork_status(philo->right_fork, UNUSED, philo->mutex_right);
}

static void	end_eat(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	philo->start_starve = get_time(philo);
	if (info->eat_time > info->die_time)
	{
		if (check_die_in_usleep(philo, info->die_time) == DIE)
			return ;
		return (philo_starve(philo));
	}
	if (check_die_in_usleep(philo, info->eat_time) == DIE)
		return ;
	change_fork_status(philo->left_fork, UNUSED, philo->mutex_left);
	change_fork_status(philo->right_fork, UNUSED, philo->mutex_right);
	(philo->eat_count)++;
	if (philo->eat_count == info->must_eat_count)
	{
		lock(info->mutex_info);
		(info->eat_finish)--;
		unlock(info->mutex_info);
	}
}

static void	philo_sleep(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	if (philo->live == DIE)
		return ;
	printf("%ld %d is sleeping\n", get_time(philo), philo->philo_num);
	if (info->eat_time + info->sleep_time > info->die_time)
	{
		if (check_die_in_usleep(philo, info->die_time - info->eat_time) == DIE)
			return ;
		philo_starve(philo);
		return ;
	}
	check_die_in_usleep(philo, info->sleep_time);
}
