/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:17:00 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/09 17:01:14 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	free_fork_info_philo_threads(int *fork, t_info *info, \
								t_philo **philo, pthread_t *threads)
{
	free(threads);
	return (free_fork_info_philo(fork, info, philo));
}

int	free_fork_mutex(pthread_mutex_t **fork, int count)
{
	int	idx;

	idx = 0;
	while (idx < count)
	{
		free(fork[idx]);
		idx++;
	}
	free(fork);
	return (1);
}

int	free_fork(int *fork)
{
	free(fork);
	return (1);
}
