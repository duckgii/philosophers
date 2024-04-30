/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:53:20 by yeoshin           #+#    #+#             */
/*   Updated: 2024/04/30 10:12:22 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include "./libft/libft.h"
# include <pthread.h>

typedef struct s_philo{
	int				die;
	int				eat_time;
	int				sleep_time;
	int				eat_count;
	int				*left_fork;
	int				*right_fork;
	int				philo_num;
	pthread_mutex_t	*mutex;
}	t_philo;

enum {
	EMPTY = 1,
	HAVE,
};

t_philo			**init_philo(char *av[]);
void			*ft_malloc(int size);
void			*thread_function(void *arg);
pthread_mutex_t	*mutex_init(void);


#endif
