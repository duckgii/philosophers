/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:58:11 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/03 19:45:13 by yeoshin          ###   ########.fr       */
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
	philo = parse_philo(av);
	info = init_info(ac, av);
	start_process(philo, info);
}

static void	start_process(t_philo *philo, t_info *info)
{
	int		idx;
	pid_t	*pid;

	idx = 0;
	pid = ft_malloc(sizeof(int) * info->philo_count);
	philo->start_time = get_time(philo);
	philo->adjust_time = 100 * (info->philo_count + 50);
	philo->start_print = 0;
	while (idx < info->philo_count)
	{
		philo->philo_num = idx + 1;
		pid[idx] = fork();
		if (pid[idx] == 0)
			child_main(philo, info);
		else
			idx++;
	}
	while (idx > 0)
	{
		idx--;
		sem_post(philo->start_wait);
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
	while (idx < info->philo_count + flag)
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
	sem_unlink("all_eat");
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("start_wait");
	sem_close(philo->all_eat);
	sem_close(philo->fork);
	sem_close(philo->print);
	sem_close(philo->start_wait);
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
