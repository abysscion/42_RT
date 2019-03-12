/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:06:00 by fdibbert          #+#    #+#             */
/*   Updated: 2019/03/12 12:11:29 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	cast_rgb(int i)
{
	t_clr color;

	color.b = (i & 0xFF) / 4;
	color.g = ((i >> 8) & 0xFF) / 4;
	color.r = ((i >> 16) & 0xFF) / 4;
	return (color.b + (color.g << 8) + (color.r << 16));
}

static int	check_difference(int i, int j)
{
	int p_one[3];
	int	p_two[3];

	p_one[0] = i & 0xFF;
	p_two[0] = j & 0xFF;
	p_one[1] = (i & 0xFF00) >> 8;
	p_two[1] = (j & 0xFF00) >> 8;
	p_one[2] = (i & 0xFF0000) >> 16;
	p_two[2] = (j & 0xFF0000) >> 16;
	if (p_one[0] - p_two[0] > 25 || p_one[0] - p_two[0] < -25)
		return (1);
	if (p_one[1] - p_two[1] > 25 || p_one[1] - p_two[1] < -25)
		return (1);
	if (p_one[2] - p_two[2] > 25 || p_one[2] - p_two[2] < -25)
		return (1);
	return (0);
}

static int	check_pixel(t_env *env, int i, int j)
{
	int mass;

	mass = env->mlx.image[j + (i * WIN_H)];
	if (i - 1 <= 0)
		if (check_difference(mass,
			env->mlx.image[j + ((i - 1) * WIN_H)]))
			return (1);
	if (j - 1 >= 0)
		if (check_difference(mass,
			env->mlx.image[j - 1 + (i * WIN_H)]))
			return (1);
	if (j + 1 < WIN_W)
		if (check_difference(mass,
			env->mlx.image[j + 1 + (i * WIN_H)]))
			return (1);
	if (i + 1 < WIN_H)
		if (check_difference(mass,
			env->mlx.image[j + ((i + 1) * WIN_H)]))
			return (1);
	return (0);
}

void	anti_aliasing(t_env *env)
{
	int i;
	int j;

	i = WIN_H / 2 * -1;
	while (i < WIN_H / 2)
	{
		j = WIN_W / 2 * -1;
		while (j < WIN_H / 2)
		{
			if (check_pixel(env, i + WIN_H / 2, j + WIN_W / 2))
			{
				anti_aliasing_render(env, i * 2, j * 2);
				env->mlx.image[j + (WIN_W / 2) +
					((i + WIN_H / 2) * (WIN_H))] =
					(cast_rgb(env->aliasing[0])) +
					(cast_rgb(env->aliasing[1])) +
					(cast_rgb(env->aliasing[2])) +
					(cast_rgb(env->aliasing[3]));
			}
			j++;
		}
		i++;
	}
}
