/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:44:27 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/25 19:35:58 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

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
