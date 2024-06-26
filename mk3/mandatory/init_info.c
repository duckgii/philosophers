/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:38:33 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/25 16:58:44 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int				init_info_mutex(t_info *info);
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
	if (init_info_mutex(info) == FALSE)
		return (free_one(info->fork));
	info->mutex_fork = malloc_mutex_fork(ft_atoi(av[1]));
	if (info->mutex_fork == NULL)
	{
		free(info->fork);
		return (free_malloc_mutex(info->mutex_info, 6));
	}
	return (info);
}

static int	init_info_mutex(t_info *info)
{
	int		idx;

	idx = 0;
	info->mutex_info = malloc(sizeof(pthread_mutex_t *) * MUTEX_SIZE);
	if (info->mutex_info == NULL)
		return (FALSE);
	while (idx < MUTEX_SIZE)
	{
		info->mutex_info[idx] = malloc(sizeof(pthread_mutex_t));
		if (info->mutex_info == NULL)
		{
			free_malloc_mutex(info->mutex_info, idx);
			return (FALSE);
		}
		idx++;
	}
	while (idx > 0)
	{
		idx--;
		pthread_mutex_init(info->mutex_info[idx], NULL);
	}
	return (TRUE);
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
