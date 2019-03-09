/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:06:00 by fdibbert          #+#    #+#             */
/*   Updated: 2019/03/09 17:18:16 by fdibbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static int	cast_rgb(int i)
{
	int rgb[3];

	rgb[0] = (i & 0xFF) / 4;
	rgb[1] = ((i >> 8) & 0xFF) / 4;
	rgb[2] = ((i >> 16) & 0xFF) / 4;
	return (rgb[0] + (rgb[1] << 8) + (rgb[2] << 16));
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

static int	check_pixel(t_env *e, int i, int j)
{
	int mass[1];

	mass[0] = e->cam->view_port_addr[j + (i * WIN_H)];
	if (i - 1 <= 0)
		if (check_difference(mass[0],
			e->cam->view_port_addr[j + ((i - 1) * WIN_H)]))
			return (1);
	if (j - 1 >= 0)
		if (check_difference(mass[0],
			e->cam->view_port_addr[j - 1 + (i * WIN_H)]))
			return (1);
	if (j + 1 < WIN_W)
		if (check_difference(mass[0],
			e->cam->view_port_addr[j + 1 + (i * WIN_H)]))
			return (1);
	if (i + 1 < WIN_H)
		if (check_difference(mass[0],
			e->cam->view_port_addr[j + ((i + 1) * WIN_H)]))
			return (1);
	return (0);
}

void	anti_aliasing(t_env *e)
{
	int i;
	int j;

	i = WIN_H / 2 * -1;
	while (i < WIN_H / 2)
	{
		j = WIN_W / 2 * -1;
		while (j < WIN_H / 2)
		{
			if (check_pixel(e, i + WIN_H / 2, j + WIN_W / 2))
			{
				aliasing_render(e, i * 2, j * 2);
				e->cam->view_port_addr[j + (WIN_W / 2) +
					((i + WIN_H / 2) * (WIN_H))] =
					(cast_rgb(e->aliasing[0])) +
					(cast_rgb(e->aliasing[1])) +
					(cast_rgb(e->aliasing[2])) +
					(cast_rgb(e->aliasing[3]));
			}
			j++;
		}
		i++;
	}
}
