/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepia_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:31:31 by fdibbert          #+#    #+#             */
/*   Updated: 2019/03/30 19:55:33 by fdibbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_clr	cast_in_sepia(int i)
{
	t_clr	color;
	double	sepia;

	color.b = ((i >> 8) & 0xFF) / 3;
	color.g = (i & 0xFF) / 3;
	color.r = ((i >> 16) & 0xFF) / 3;
	sepia = color.b + color.g + color.r;
	color.b = sepia * 0.33;
	color.g = sepia * 0.6;
	color.r = sepia * 0.9;
	return (color);
}

void			sepia(t_env *env)
{
	int		x;
	int		y;
	t_clr	color;

	y = WIN_H / 2 * -1;
	while (y < WIN_H / 2)
	{
		x = WIN_W / 2 * -1;
		while (x < WIN_W / 2)
		{
			color = cast_in_sepia(env->sdl.image[WIN_W *
					(y + WIN_H / 2) + (x + WIN_W / 2)]);
			env->sdl.image[WIN_W * (y + WIN_H / 2) + (x + WIN_W / 2)] =
				(color.r << 16) + (color.b << 8) + (color.g);
			sdl_draw(env, color, x, y);
			x++;
		}
		y++;
	}
}