/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:15:35 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/11 17:38:21 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	after_point(char *str)
{
	double	result;
	double	multiplier;

	result = 0;
	multiplier = 0.1;
	while (*str == '\t' || *str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result + (*str - '0') * multiplier;
		multiplier *= 0.1;
		str++;
	}
	return (result);
}

static double	before_point(char *str, int *sign)
{
	double	result;

	result = 0;
	while (*str == '\t' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result);
}

double			ft_atod(char *str)
{
	char	**split;
	double	b_point;
	double	a_point;
	int		sign;

	sign = 1;
	split = ft_strsplit(str, '.');
	b_point = before_point(split[0], &sign);
	a_point = after_point(split[1]);
	free_words(split);
	return ((double)sign * (b_point + a_point));
}
