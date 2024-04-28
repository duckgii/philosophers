/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:21:57 by yeoshin           #+#    #+#             */
/*   Updated: 2024/04/28 17:29:06 by yeoshin          ###   ########.fr       */
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
	int			i;

	ac = 1;
	idx = 0;
	arg = init_av(av);
	threads = ft_malloc(sizeof(pthread_t) * arg->member);
	while (idx < arg->member)
	{
		arg->my_number = idx;
		res = pthread_create(&threads[idx], NULL, thread_function, &threads[idx]);
		if (res != 0)
		{
			printf("main thread is failed");
			return (1);
		}
		idx++;
	}
	i = 0;
	while (i < arg->member)
	{
		res = pthread_join(threads[i], &thread_result);
		if (res != 0)
		{
			printf("main thread is failed");
			return (1);
		}
		i++;
	}
	return (0);
}

//void *thread_function(void *arg)
//{
//    /* 인자로 받은 값을 my_number에 저장한다. */
//    int my_number = *((int*)(&arg));
//    int rand_num;

//    /* 몇번째 pthread가 실행중인지 메시지를 출력한다. */
//    printf("[thread(%d)] is running\n", my_number);

//    /* 1부터 5 사이의 임의의 값을 생성한다. */
//    rand_num = 1 + (int)(5.0*rand()/(RAND_MAX+1.0));

//    /* 생성된 임의의 값만큼 sleep한다. */
//    sleep(rand_num);

//    /* sleep이 끝났음을 메시지로 출력한다 */
//    printf("[thread(%d)] job done\n", my_number);

//    /* thread 작업이 종료되었음을 알린다. */
//    pthread_exit(NULL);
//}
void	*thread_function(void *arg)
{
	int		my_num;
	int		eat_count;

	my_num = *(int *)arg;
	printf("philosopher %d is here!\n", my_num);
	return (NULL);
}
