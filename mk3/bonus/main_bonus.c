/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:58:11 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/26 01:34:59 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void	start_process(t_philo *philo, t_info *info);
static void	end_process(t_philo	*philo, int	*pid, int count);
static void	check_arg(int ac, char *av[]);
static void	wait_process(t_philo *philo, t_info *info);

int	main(int ac, char *av[])
{
	t_philo		*philo;
	t_info		*info;

	check_arg(ac, av);
	philo = parse_philo(ac, av);
	info = init_info(ac, av);
	start_process(philo, info);
	exit(0);
}

static void	start_process(t_philo *philo, t_info *info)
{
	int		idx;
	pid_t	*pid;

	idx = 0;
	pid = ft_malloc(sizeof(int) * info->philo_count);
	philo->start_time = get_time(philo);
	philo->start_starve = philo->start_time;
	philo->start_print = philo->start_time;
	while (idx < info->philo_count)
	{
		philo->philo_num = idx + 1;
		pid[idx] = fork();
		if (pid == 0)
			child_main(philo, info);
		idx++;
	}
	if (pid > 0)
		wait_process(philo, info);
	end_process(philo, pid, info->philo_count);
}

static void	wait_process(t_philo *philo, t_info *info)
{
	int		idx;
	int		flag;

	idx = 0;
	flag = 0;
	if (info->must_eat_count == -1)
		flag = 1;
	while (idx < info->philo_count + 1)
	{
		sem_wait(philo->all_eat);
		idx++;
	}
}

static void	end_process(t_philo	*philo, int	*pid, int count)
{
	int		idx;

	idx = 0;
	while (idx < count)
	{
		kill(pid[idx], 1);
		idx++;
	}
}

static void	check_arg(int ac, char *av[])
{
	int		flag;

	flag = TRUE;
	if (ac < 5 || ac > 6)
		flag = FALSE;
	if (flag == TRUE)
	{
		if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 \
		|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
			flag = FALSE;
		if (ac == 6)
		{
			if (ft_atoi(av[5]) <= 0)
				flag = FALSE;
		}
	}
	if (flag == FALSE)
	{
		printf("Arguments are invalid!!\n");
		exit(1);
	}
}
