/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:27:43 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/25 22:24:16 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	*ft_malloc(int size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		exit(1);
	return (ret);
}

long	get_time(t_philo *philo)
{
	struct timeval	mytime;
	long			time;

	gettimeofday(&mytime, NULL);
	time = (mytime.tv_sec * 1000000) + mytime.tv_usec;
	return (time - philo->start_time);
}