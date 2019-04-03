/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereoscopy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:53:39 by fdibbert          #+#    #+#             */
/*   Updated: 2019/04/02 20:12:38 by fdibbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		left_stereoscopy(t_env *env, int w_w)
{
	int		y;
	int		x;
	t_v		dest;
	t_clr	color;

	env->cam.position.x -= 0.1;
	env->cam.rotation.y += 0.2;
	y = WIN_H / 2 * -1;
	while (y < WIN_H / 2)
	{
		x = w_w / 2 * -1;
		while (x < w_w / 2)
		{
			dest = (t_v){x * 1.0 / (w_w), y * -1.0 / WIN_H, 1.0};
			dest = vecnorm(vec_rotate(env->cam.rotation, dest));
			init_ray(env, dest);
			color = trace_ray(env, RECURSION);
			env->sdl.image[WIN_W * (y + WIN_H / 2) + (x + w_w / 2)] =
				(color.r << 16) + (color.b << 8) + color.g;
			sdl_draw(env, color, (x - w_w / 2), y);
			x++;
		}
		y++;
	}
}

static void		right_stereoscopy(t_env *env, int w_w)
{
	int		y;
	int		x;
	t_v		dest;
	t_clr	color;

	env->cam.position.x += 0.2;
	env->cam.rotation.y -= 0.4;
	y = WIN_H / 2 * -1;
	while (y < WIN_H / 2)
	{
		x = w_w / 2 * -1;
		while (x < w_w / 2)
		{
			dest = (t_v){x * 1.0 / (w_w), y * -1.0 / WIN_H, 1.0};
			dest = vecnorm(vec_rotate(env->cam.rotation, dest));
			init_ray(env, dest);
			color = trace_ray(env, RECURSION);
			env->sdl.image[WIN_W * (y + WIN_H / 2) + (x + (w_w + w_w / 2))] =
				(color.r << 16) + (color.b << 8) + color.g;
			sdl_draw(env, color, (x + w_w / 2), y);
			x++;
		}
		y++;
	}
}

void	stereoscopy(t_env *env)
{
	int windows_w;

	windows_w = WIN_W / 2;
	left_stereoscopy(env, windows_w);
	printf("privet\n");
	right_stereoscopy(env, windows_w);
	env->cam.position.x -= 0.1;
	env->cam.rotation.y += 0.2;
}