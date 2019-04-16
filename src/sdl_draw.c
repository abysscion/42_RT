/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:18:17 by fdibbert          #+#    #+#             */
/*   Updated: 2019/04/16 19:32:49 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	sdl_help(t_env *env, int x, int y)
{
	t_clr color;

	color.g = env->sdl.image[x + y * RT__W] & 0xFF;
	color.b = (env->sdl.image[x + y * RT__W] & 0xFF00) >> 8;
	color.r = (env->sdl.image[x + y * RT__W] & 0xFF0000) >> 16;
	sdl_draw(env, color, x - RT__W / 2, y - RT__H / 2);
}

void	sdl_draw(t_env *env, t_clr color, int x, int y)
{
	SDL_SetRenderDrawColor(env->sdl.renderer, color.r, color.g, color.b, 0);
	SDL_RenderDrawPoint(env->sdl.renderer, x + env->constants.half_render_w
		+ GUI_LBLOCK_W, y + env->constants.half_render_h + kiss_edge * 2);
}

/*
**	Takes sdl.image content and draws every pixel of it on renderer.
*/

void	draw_rt(t_env *env)
{
	int		x;
	int		y;
	t_clr	color;

	y = -1;
	while (++y < RT__H)
	{
		x = -1;
		while (++x < RT__W)
		{
			color.g = env->sdl.image[x + y * RT__W] & 0xFF;
			color.b = (env->sdl.image[x + y * RT__W] & 0xFF00) >> 8;
			color.r = (env->sdl.image[x + y * RT__W] & 0xFF0000) >> 16;
			sdl_draw(env, color, x - env->constants.half_render_w,
									y - env->constants.half_render_h);
		}
	}
}
