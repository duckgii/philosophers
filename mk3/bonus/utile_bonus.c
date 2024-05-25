/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:27:43 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/25 22:51:08 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static int	check_long(const char *str, int flag);
static int	len_use(const char *string);

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

int	ft_atoi(const char *str)
{
	int			flag;
	long long	num;

	flag = 1;
	num = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
			str ++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			flag *= -1;
		str ++;
	}
	while (*str == '0')
		str ++;
	if (check_long(str, flag) != 1)
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - 48;
		str ++;
	}
	return (flag * num);
}

static int	len_use(const char *string)
{
	int		len;

	len = 0;
	while (*string >= '0' && *string <= '9')
	{
		len ++;
		string ++;
	}
	return (len);
}

static int	check_long(const char *str, int flag)
{
	int	length;

	length = len_use(str);
	if (length < 19)
		return (1);
	else if (length > 19)
	{
		if (flag == -1)
			return (0);
		return (-1);
	}
	if (flag == -1 && (ft_strncmp("9223372036854775808", str, 19) < 0))
		return (-1);
	else if (flag == 1 && (ft_strncmp("9223372036854775807", str, 19) < 0))
		return (-1);
	return (1);
}

