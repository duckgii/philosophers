/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:21:57 by yeoshin           #+#    #+#             */
/*   Updated: 2024/04/28 15:26:29 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char *av[])
{
	t_arg		*arg;
	pthread_t	*threads;
	void		*thread_result;
	int			res;
	int			idx;

	idx = 0;
	arg = init_av(av);
	threads = ft_malloc(sizeof(pthread_t));
	while (idx < arg->member)
	{
		arg->my_number = idx;
		res = pthread_create(threads[idx], NULL, thread_function, (void *)arg);
		if (res != 0)
		{
			printf("main thread is failed");
			return (1);
		}
		idx++;
	}
	idx = 0;
	while (idx < arg->member)
	{
		res = pthread_join(threads[idx], &thread_result);
		if (res != 0)
		{
			printf("main thread is failed");
			return (1);
		}
		idx++;
	}
	return (0);
}

void	*thread_function(void *arg)
{
	int		my_num;

	my_num = ((t_arg *)arg)->my_number;
	printf("123");
}
