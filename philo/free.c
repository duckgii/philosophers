/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:08:52 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/06 22:21:26 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	free_fork(int *fork)
{
	free(fork);
	return (1);
}

void	*free_philo(t_philo **ret, int count)
{
	int		idx;

	idx = 0;
	while (idx < count && ret[idx] != NULL)
	{
		free(ret[idx]->mutex_left);
		free(ret[idx]->mutex_right);
		free(ret[idx]);
		idx++;
	}
	return (NULL);
}

int	free_philo_fork(t_philo **ret, int count, int *fork)
{
	int		idx;

	idx = 0;
	free_fork(fork);
	while (ret[idx] != NULL && idx < count)
	{
		free(ret[idx]);
		idx++;
	}
	return (1);
}

int	free_philo_monitor_fork(t_philo **philo, t_monitor *monitor, \
							int count, int *fork)
{
	free_fork(fork);
	free_philo(philo, count);
	free(monitor);
	return (1);
}
