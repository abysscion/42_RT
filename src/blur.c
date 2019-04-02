/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 20:38:13 by fdibbert          #+#    #+#             */
/*   Updated: 2019/04/02 18:18:36 by fdibbert         ###   ########.fr       */
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
	*iy = MIN(y + moty, WIN_H - 1) + 1;
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
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
		{
			init_wy(&weights[0], &iy, y, moty);
			while (--iy > y)
				calc_weights(&weights[0], blur->img[iy * WIN_W + x], 2);
			ix = MIN(x + motx, WIN_W - 1) + 1;
			while (--ix > x)
				calc_weights(&weights[0], blur->img[y * WIN_W + ix], 1);
			e->sdl.image[x + y * WIN_W] = weights[0] / weights[3] +
				((int)(weights[1] / weights[4]) << 8) +
				((int)(weights[2] / weights[5]) << 16);
			sdl_help(e, x, y);
		}
	}
}

void		blur(t_env *env)
{
	t_blur	*blur;

	blur = malloc(sizeof(t_blur));
	blur->img = malloc(sizeof(int) * WIN_W * WIN_H * 4);
	ft_memcpy(blur->img, env->sdl.image, WIN_H * WIN_W * 4);
	motion_blur(env, blur, 4, 4);
	free(blur->img);
	free(blur);
}
