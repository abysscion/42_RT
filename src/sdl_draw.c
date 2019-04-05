/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:18:17 by fdibbert          #+#    #+#             */
/*   Updated: 2019/04/03 09:25:05 by sb_fox           ###   ########.fr       */
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
	SDL_RenderDrawPoint(env->sdl.renderer, x + env->abuse.hrw + GUI_LBLOCK_W,
											y + env->abuse.hrh + GUI_BAR_H);
}
