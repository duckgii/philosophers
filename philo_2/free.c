/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:57:24 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/09 17:01:34 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*free_one(void	*target)
{
	free(target);
	return (NULL);
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

int	free_fork_info(int *fork, t_info *info)
{
	free(fork);
	free(info->mutex_info);
	free_fork_mutex(info->mutex_fork, info->philo_count);
	free(info);
	return (1);
}

int	free_fork_info_philo(int *fork, t_info *info, t_philo **philo)
{
	int		count;
	int		idx;

	idx = 0;
	count = info->philo_count;
	while (idx < count)
	{
		free(philo[idx]->right_fork);
		idx++;
	}
	free_fork_info(fork, info);
	free(philo);
	return (1);
}
