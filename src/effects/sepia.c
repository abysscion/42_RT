/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:31:31 by fdibbert          #+#    #+#             */
/*   Updated: 2019/04/17 20:26:08 by fdibbert         ###   ########.fr       */
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

	y = env->constants.half_render_h * -1;
	while (y < env->constants.half_render_h)
	{
		x = env->constants.half_render_w * -1;
		while (x < env->constants.half_render_w)
		{
			color = cast_in_sepia(env->sdl.image[RT__W *
					(y + env->constants.half_render_h)
					+ (x + env->constants.half_render_w)]);
			env->sdl.image[RT__W *
					(y + env->constants.half_render_h) +
					(x + env->constants.half_render_w)] =
					(color.r << 16) + (color.b << 8) + (color.g);
			x++;
		}
		y++;
	}
}
