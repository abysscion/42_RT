/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereoscopy_antialiasing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 19:38:41 by fdibbert          #+#    #+#             */
/*   Updated: 2019/04/17 19:42:38 by fdibbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	left_anti_aliasing_render(t_env *env, t_clr *aliasing, int i, int j)
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
			dest = (t_v){x * 1.0 / (RT__W), y * -1.0 / (RT__H * 2), 1.0};
			dest = vecnorm(vec_rotate(env->cam.rotation, dest));
			init_ray(env, dest);
			aliasing[k] = trace_ray(env, RECURSION);
			k++;
			x++;
		}
		y++;
	}
}

static void	right_anti_aliasing_render(t_env *env, t_clr *aliasing, int i, int j)
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
			dest = (t_v){x * 1.0 / (RT__W), y * -1.0 / (RT__H * 2), 1.0};
			dest = vecnorm(vec_rotate(env->cam.rotation, dest));
			init_ray(env, dest);
			aliasing[k] = trace_ray(env, RECURSION);
			k++;
			x++;
		}
		y++;
	}
}

static void			left_stereo_anti_aliasing(t_env *env)
{
	int		y;
	int		x;
	t_clr	color;
	t_clr	aliasing[4];

	env->cam.position.x -= 0.1;
	env->cam.rotation.y += 0.2;
	y = env->constants.half_render_h * -1;
	while (y < env->constants.half_render_h)
	{
		x = (env->constants.half_render_w / 2) * -1;
		while (x < env->constants.half_render_w / 2)
		{
			if (check_pixel(env, y + env->constants.half_render_h,
				x + (env->constants.half_render_w / 2)))
			{
				left_anti_aliasing_render(env, &aliasing[0], y * 2, x * 2);
				sum_color(&aliasing[0], &color);
				env->sdl.image[RT__W * (y + env->constants.half_render_h) +
						(x + (env->constants.half_render_w / 2))] =
					(color.r << 16) + (color.b << 8) + (color.g);
			}
			x++;
		}
		y++;
	}
}

static void			right_stereo_anti_aliasing(t_env *env)
{
	int		y;
	int		x;
	t_clr	color;
	t_clr	aliasing[4];

	env->cam.position.x += 0.2;
	env->cam.rotation.y -= 0.4;
	y = env->constants.half_render_h * -1;
	while (y < env->constants.half_render_h)
	{
		x = (env->constants.half_render_w / 2) * -1;
		while (x < (env->constants.half_render_w / 2))
		{
			if (check_pixel(env, y + env->constants.half_render_h,
				x + (env->constants.half_render_w + env->constants.half_render_w / 2)))
			{
				right_anti_aliasing_render(env, &aliasing[0], y * 2, x * 2);
				sum_color(&aliasing[0], &color);
				env->sdl.image[RT__W * (y + env->constants.half_render_h) +
						(x + (int)(env->constants.half_render_w * 1.5))] =
					(color.r << 16) + (color.b << 8) + (color.g);
			}
			x++;
		}
		y++;
	}
}

void			stereo_aliasing(t_env *env)
{
	left_stereo_anti_aliasing(env);
	right_stereo_anti_aliasing(env);
	env->cam.position.x -= 0.1;
	env->cam.rotation.y += 0.2;
}
