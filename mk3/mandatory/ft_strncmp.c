/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:09:58 by yeoshin           #+#    #+#             */
/*   Updated: 2024/05/14 20:53:12 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			idx;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	idx = 0;
	if (n == 0)
		return (0);
	while (idx < n)
	{
		if (str1[idx] != str2[idx])
			return (str1[idx] - str2[idx]);
		else if (str1[idx] == '\0')
			break ;
		idx ++;
	}
	return (0);
}
