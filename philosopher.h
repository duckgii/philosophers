/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:53:20 by yeoshin           #+#    #+#             */
/*   Updated: 2024/04/28 15:21:08 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include "./libft/libft.h"
# include <pthread.h>

typedef struct s_arg{
	int		member;
	int		die;
	int		eat;
	int		sleep;
	int		must_eat;
	int		my_number;
}	t_arg;

void	*ft_malloc(int size);

#endif
