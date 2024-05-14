/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:49:37 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/14 18:36:35 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*free_one(void	*pointer)
{
	free(pointer);
	return (NULL);
}

void	*free_malloc_philos(t_philo **ret, int count)
{
	int		idx;

	idx = 0;
	while (idx < count)
	{
		free(ret[idx]);
		idx++;
	}
	free(ret);
	return (NULL);
}

void	*free_malloc_mutex(pthread_mutex_t **ret, int count)
{
	int		idx;

	idx = 0;
	while (idx < count)
	{
		free(ret[idx]);
		idx++;
	}
	free(ret);
	return (NULL);
}

void	*free_malloc_threads(pthread_t **ret, int count)
{
	int		idx;

	idx = 0;
	while (idx < count)
	{
		free(ret[idx]);
		idx++;
	}
	free(ret);
	return (NULL);
}
