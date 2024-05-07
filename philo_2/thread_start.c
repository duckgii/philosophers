/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:41:48 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/07 14:41:41 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	end_eat(t_main *main);
static void	philo_eat(t_main *main);
static void	philo_sleep(t_main	*main);

void	*thread_function(void *info)
{
	t_main	*main;
	t_philo	*philo;

	main = (t_main *)info;
	philo = main->philo;
	philo->start_time = get_time(philo);
	while (1)
	{
		philo_eat(main);
		philo_sleep(main);
		lock(main->mutex_main);
		if (main->live == DIE)
		{
			unlock(main->mutex_main);
			check_and_change_die(main->philo);
			break ;
		}
		unlock(main->mutex_main);
	}
	return (NULL);
}

static void	philo_eat(t_main *main)
{
	int		check;
	t_philo	*philo;

	check = FALSE;
	philo = main->philo;
	printf("%ld %d is thinking\n", get_time(philo), philo->philo_num);
	while (check == FALSE)
	{
		if (philo->live == DIE)
			return ;
		if (get_time(philo) - philo->start_starve > main->die_time)
			return (philo_starve(main));
		check = get_first_fork(philo);
	}
	check = FALSE;
	while (check == FALSE)
	{
		if (get_time(philo) - philo->start_starve > main->die_time)
			return (philo_starve(main));
		check = get_second_fork(philo);
	}
	printf("%ld %d is eating\n", get_time(philo), philo->philo_num);
	end_eat(main);
}

void	philo_starve(t_main *main)
{
	t_philo	*philo;

	philo = main->philo;
	if (philo->live == DIE)
		return ;
	philo->live = DIE;
	lock(main->mutex_main);
	main->live = DIE;
	unlock(main->mutex_main);
	printf("%ld %d died\n", get_time(philo), philo->philo_num);
	change_fork_status(philo->left_fork, UNUSED, philo->mutex_left);
	change_fork_status(philo->right_fork, UNUSED, philo->mutex_right);
}

static void	end_eat(t_main *main)
{
	t_philo	*philo;

	philo = main->philo;
	philo->start_starve = get_time(philo);
	if (main->eat_time > main->die_time)
	{
		if (check_die_in_usleep(main, main->die_time) == DIE)
			return ;
		return (philo_starve(main));
	}
	if (check_die_in_usleep(main, main->eat_time) == DIE)
		return ;
	change_fork_status(philo->left_fork, UNUSED, philo->mutex_left);
	change_fork_status(philo->right_fork, UNUSED, philo->mutex_right);
	(philo->eat_count)++;
}

static void	philo_sleep(t_main	*main)
{
	t_philo	*philo;

	philo = main->philo;
	if (philo->live == DIE)
		return ;
	printf("%ld %d is sleeping\n", get_time(philo), philo->philo_num);
	if (main->eat_time + main->sleep_time > main->die_time)
	{
		if (check_die_in_usleep(main, main->die_time - main->eat_time) == DIE)
			return ;
		philo_starve(main);
		return ;
	}
	check_die_in_usleep(main, main->sleep_time);
}
