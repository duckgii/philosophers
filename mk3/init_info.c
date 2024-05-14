/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:38:33 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/14 17:07:45 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static pthread_mutex_t	**malloc_mutex_fork(int count);

t_info	*malloc_info(t_info *info, char *av[])
{
	int		idx;

	idx = 0;
	info->fork = malloc(sizeof(int) * ft_atoi(av[1]));
	if (info->fork == NULL)
		return (NULL);
	while (idx < ft_atoi(av[1]))
	{
		info->fork[idx] = UNUSED;
		idx++;
	}
	info->mutex_info = malloc(sizeof(pthread_mutex_t));
	if (info->mutex_info == NULL)
		return (free_one(info->fork));
	info->mutex_fork = malloc_mutex_fork(ft_atoi(av[1]));
	if (info->mutex_fork == NULL)
	{
		free(info->fork);
		return (free_one(info->mutex_info));
	}
	return (info);
}

static pthread_mutex_t	**malloc_mutex_fork(int count)
{
	int				idx;
	pthread_mutex_t	**ret;

	idx = 0;
	ret = malloc(sizeof(pthread_mutex_t *) * count);
	if (ret == NULL)
		return (NULL);
	while (idx < count)
	{
		ret[idx] = malloc(sizeof(pthread_mutex_t));
		if (ret[idx] == NULL)
			return (free_malloc_mutex(ret, idx));
		pthread_mutex_init(ret[idx], NULL);
		idx++;
	}
	return (ret);
}
