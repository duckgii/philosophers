/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:57:24 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/07 11:17:58 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*free_one(void	*target)
{
	free(target);
	return (NULL);
}

int	free_fork(int *fork)
{
	free(fork);
	return (1);
}

void	*free_philo(t_philo **philo, int count)
{
	int		idx;

	idx = 0;
	while (idx <= count)
	{
		free(philo[idx]);
		idx++;
	}
	free(philo);
	return (NULL);
}

int	free_fork_main(int *fork, t_main *main)
{
	free(fork);
	free(main->mutex_main);
	free(main->mutex_fork);
	free(main);
	return (1);
}

int	free_fork_main_philo(int *fork, t_main *main, t_philo **philo)
{
	int		count;
	int		idx;

	idx = 0;
	count = main->philo_count;
	while (idx < count)
	{
		free(philo[idx]->right_fork);
		idx++;
	}
	free(philo);
	return (free_fork_main(fork, main));
}
