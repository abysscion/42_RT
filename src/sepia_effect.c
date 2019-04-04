/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepia_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:31:31 by fdibbert          #+#    #+#             */
/*   Updated: 2019/04/04 03:16:39 by sb_fox           ###   ########.fr       */
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

	y = env->abuse.hrh * -1;
	while (y < env->abuse.hrh)
	{
		x = env->abuse.hrw * -1;
		while (x < env->abuse.hrw)
		{
			color = cast_in_sepia(env->sdl.image[RT__W *
					(y + env->abuse.hrh) + (x + env->abuse.hrw)]);
			env->sdl.image[RT__W *
					(y + env->abuse.hrh) + (x + env->abuse.hrw)] =
					(color.r << 16) + (color.b << 8) + (color.g);
			x++;
		}
		y++;
	}
}
