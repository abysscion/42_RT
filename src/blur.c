/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 20:38:13 by fdibbert          #+#    #+#             */
/*   Updated: 2019/04/04 03:17:28 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)

static void	init_wy(double *weights, int *iy, int y, int moty)
{
	weights[0] = 0;
	weights[1] = 0;
	weights[2] = 0;
	weights[3] = 0;
	weights[4] = 0;
	weights[5] = 0;
	*iy = MIN(y + moty, RT__H - 1) + 1;
}

static void	calc_weights(double *weights, int color, int weight)
{
	weights[0] += color & 0xFF;
	weights[1] += ((color & 0xFF00) >> 8);
	weights[2] += ((color & 0xFF0000) >> 16);
	weights[3] += weight;
	weights[4] += weight;
	weights[5] += weight;
}

static void	motion_blur(t_env *e, t_blur *blur, int motx, int moty)
{
	int			x;
	int			y;
	double		weights[6];
	int			iy;
	int			ix;

	y = -1;
	while (++y < RT__H)
	{
		x = -1;
		while (++x < RT__W)
		{
			init_wy(&weights[0], &iy, y, moty);
			while (--iy > y)
				calc_weights(&weights[0], blur->img[iy * RT__W + x], 2);
			ix = MIN(x + motx, RT__W - 1) + 1;
			while (--ix > x)
				calc_weights(&weights[0], blur->img[y * RT__W + ix], 1);
			e->sdl.image[x + y * RT__W] = weights[0] / weights[3] +
				((int)(weights[1] / weights[4]) << 8) +
				((int)(weights[2] / weights[5]) << 16);
		}
	}
}

void		blur(t_env *env)
{
	t_blur	*blur;

	blur = malloc(sizeof(t_blur));
	blur->img = malloc(sizeof(int) * RT__W * RT__H * 4);
	ft_memcpy(blur->img, env->sdl.image, RT__H * RT__W * 4);
	motion_blur(env, blur, 4, 4);
	free(blur->img);
	free(blur);
}
