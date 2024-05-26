/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_print_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:22:51 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/26 11:41:03 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	print_get_fork(t_philo *philo)
{
	sem_wait(philo->print);
	printf("%ld %d has taken a fork\n", get_time(philo) / 1000, \
	philo->philo_num);
	sem_post(philo->print);
}

void	print_philo_eat(t_philo *philo)
{
	sem_wait(philo->print);
	philo->start_print = get_time(philo);
	philo->start_starve = philo->start_print;
	printf("%ld %d is eating\n", philo->start_print / 1000, \
	philo->philo_num);
	sem_post(philo->print);
}

void	print_philo_died(t_philo *philo)
{
	sem_wait(philo->print);
	printf("%ld %d died\n", get_time(philo) / 1000, \
	philo->philo_num);
}

void	print_philo_sleep(t_philo *philo)
{
	sem_wait(philo->print);
	philo->start_print = get_time(philo);
	printf("%ld %d is sleeping\n", philo->start_print / 1000, \
	philo->philo_num);
	sem_post(philo->print);
}
