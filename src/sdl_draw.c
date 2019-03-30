/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:18:17 by fdibbert          #+#    #+#             */
/*   Updated: 2019/03/30 21:12:54 by fdibbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	sdl_help(t_env *env, int x, int y)
{
	t_clr color;

	color.g = env->sdl.image[x + y * WIN_H] & 0xFF;
	color.b = (env->sdl.image[x + y * WIN_H] & 0xFF00) >> 8;
	color.r = (env->sdl.image[x + y * WIN_H] & 0xFF0000) >> 16;
	sdl_draw(env, color, x - WIN_W / 2, y - WIN_H / 2);
}

void	sdl_draw(t_env *env, t_clr color, int x, int y)
{
	SDL_SetRenderDrawColor(env->sdl.renderer, color.r,
									color.g, color.b, 0);
	SDL_RenderDrawPoint(env->sdl.renderer, x + WIN_W / 2,
									y + WIN_H / 2);
}