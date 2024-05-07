/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:17:00 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/07 11:18:01 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	free_fork_main_philo_threads(int *fork, t_main *main, \
								t_philo **philo, pthread_t *threads)
{
	free(threads);
	return (free_fork_main_philo(fork, main, philo));
}
