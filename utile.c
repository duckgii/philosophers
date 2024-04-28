/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:05:43 by yeoshin           #+#    #+#             */
/*   Updated: 2024/04/28 15:54:31 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <stdlib.h>

t_arg	*init_av(char *av[])
{
	t_arg	*ret;

	ret = ft_malloc(sizeof(t_arg));
	ret->member = ft_atoi(av[1]);
	ret->die = ft_atoi(av[2]);
	ret->eat = ft_atoi(av[3]);
	ret->sleep = ft_atoi(av[4]);
	ret->must_eat = ft_atoi(av[5]);
	printf("%d %s %s %s %s\n", ret->member, av[2], av[3], av[4], av[5]);
	return (ret);
}

void	*ft_malloc(int size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
	{
		printf("memory allocate is falied\n");
		exit(1);
	}
	return (ret);
}

