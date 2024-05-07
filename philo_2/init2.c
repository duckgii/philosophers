/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:36:42 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/07 14:13:48 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

pthread_mutex_t	*init_mutex(int count)
{
	pthread_mutex_t	**mutex;
	int				idx;

	idx = 0;
	mutex = malloc(sizeof(pthread_mutex_t) * count);
	if (mutex == NULL)
		return (NULL);
	while (idx < count)
	{
		pthread_mutex_init(&mutex[idx], NULL);
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
