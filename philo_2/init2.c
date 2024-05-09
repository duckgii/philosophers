/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:36:42 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/09 17:03:26 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

pthread_mutex_t	**init_fork_mutex(int count)
{
	pthread_mutex_t	**mutex;
	int				idx;

	idx = 0;
	mutex = malloc(sizeof(pthread_mutex_t *) * count);
	if (mutex == NULL)
		return (NULL);
	while (idx < count)
	{
		mutex[idx] = malloc(sizeof(pthread_mutex_t));
		if (mutex[idx] == NULL)
		{
			if (idx != 0)
				free_fork_mutex(mutex, idx - 1);
			free(mutex);
			return (NULL);
		}
		pthread_mutex_init(mutex[idx], NULL);
		idx++;
	}
	return (mutex);
}

pthread_t	*init_threads(int count)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * count);
	if (threads == NULL)
		return (NULL);
	return (threads);
}
