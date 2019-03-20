/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 05:21:02 by emayert           #+#    #+#             */
/*   Updated: 2019/03/20 17:13:59 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rotation(int key, t_env *e, char *redraw)
{
	if (key == SDLK_KP_4 || key == SDLK_KP_2 ||
		key == SDLK_KP_6 || key == SDLK_KP_8)
		*redraw = 1;
	else
		return ;
	if (key == SDLK_KP_4)
		e->cam.rotation.y -= M_PI / 180 * ROT_STEP;
	else if (key == SDLK_KP_6)
		e->cam.rotation.y += M_PI / 180 * ROT_STEP;
	else if (key == SDLK_KP_2)
		e->cam.rotation.x -= M_PI / 180 * ROT_STEP;
	else if (key == SDLK_KP_8)
		e->cam.rotation.x += M_PI / 180 * ROT_STEP;
}

static void	movement(int key, t_env *e, char *redraw)
{
	if (key == SDLK_UP || key == SDLK_DOWN || key == SDLK_RIGHT ||
		key == SDLK_LEFT || key == SDLK_RSHIFT || key == SDLK_RCTRL)
		*redraw = 1;
	else
		return ;
	if (key == SDLK_RSHIFT)
		e->cam.position = vecsub(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){0, 1, 0}));
	else if (key == SDLK_RCTRL)
		e->cam.position = vecsum(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){0, 1, 0}));
	else if (key == SDLK_LEFT)
		e->cam.position = vecsub(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){1, 0, 0}));
	else if (key == SDLK_RIGHT)
		e->cam.position = vecsum(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){1, 0, 0}));
	else if (key == SDLK_UP)
		e->cam.position = vecsum(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){0, 0, 1}));
	else if (key == SDLK_DOWN)
		e->cam.position = vecsub(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){0, 0, 1}));
}

void		sdl_key_press_events(int key, t_env *env)
{
	char	redraw;

	redraw = 0;
	movement(key, env, &redraw);
	rotation(key, env, &redraw);
	if (redraw)
		render(env);
}

