/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:06:00 by fdibbert          #+#    #+#             */
/*   Updated: 2019/04/17 20:24:38 by fdibbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sum_color(t_clr *aliasing, t_clr *color)
{
	int		i;

	i = 0;
	ft_bzero(color, 3);
	while (i < 4)
	{
		color->b += aliasing[i].b / 4;
		color->g += aliasing[i].g / 4;
		color->r += aliasing[i].r / 4;
		i++;
	}
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

int			check_pixel(t_env *env, int i, int j)
{
	int mass;

	mass = env->sdl.image[j + (i * RT__W)];
	if (i - 1 >= 0)
		if (check_difference(mass,
			env->sdl.image[j + ((i - 1) * RT__W)]))
			return (1);
	if (j - 1 >= 0)
		if (check_difference(mass,
			env->sdl.image[j - 1 + (i * RT__W)]))
			return (1);
	if (j + 1 < RT__W)
		if (check_difference(mass,
			env->sdl.image[j + 1 + (i * RT__W)]))
			return (1);
	if (i + 1 < RT__H)
		if (check_difference(mass,
			env->sdl.image[j + ((i + 1) * RT__W)]))
			return (1);
	return (0);
}

static void	anti_aliasing_render(t_env *env, t_clr *aliasing, int i, int j)
{
	t_v		dest;
	int		k;
	int		x;
	int		y;

	y = i;
	k = 0;
	while (y <= i + 1)
	{
		x = j;
		while (x <= j + 1)
		{
			dest = (t_v){x * 1.0 / (RT__W * 2), y * -1.0 / (RT__H * 2), 1.0};
			dest = vecnorm(vec_rotate(env->cam.rotation, dest));
			init_ray(env, dest);
			aliasing[k] = trace_ray(env, RECURSION);
			k++;
			x++;
		}
		y++;
	}
}

void		anti_aliasing(t_env *env)
{
	int		i;
	int		j;
	t_clr	color;
	t_clr	aliasing[4];

	i = env->constants.half_render_h * -1;
	while (i < env->constants.half_render_h)
	{
		j = env->constants.half_render_w * -1;
		while (j < env->constants.half_render_w)
		{
			if (check_pixel(env, i + env->constants.half_render_h,
					j + env->constants.half_render_w))
			{
				anti_aliasing_render(env, &aliasing[0], i * 2, j * 2);
				sum_color(&aliasing[0], &color);
				env->sdl.image[RT__W * (i + env->constants.half_render_h) +
					(j + env->constants.half_render_w)] =
					(color.r << 16) + (color.b << 8) + (color.g);
			}
			j++;
		}
		i++;
	}
}
