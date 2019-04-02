/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 05:21:02 by emayert           #+#    #+#             */
/*   Updated: 2019/04/01 15:33:52 by eloren-l         ###   ########.fr       */
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
		e->cam.rotation.y -= ROT_STEP;
	else if (key == SDLK_KP_6)
		e->cam.rotation.y += ROT_STEP;
	else if (key == SDLK_KP_2)
		e->cam.rotation.x += ROT_STEP;
	else if (key == SDLK_KP_8)
		e->cam.rotation.x -= ROT_STEP;
}

static void	movement(int key, t_env *e, char *redraw)
{
	if (key == SDLK_UP || key == SDLK_DOWN || key == SDLK_RIGHT ||
		key == SDLK_LEFT || key == SDLK_RSHIFT || key == SDLK_RCTRL)
		*redraw = 1;
	else
		return ;
	if (key == SDLK_RSHIFT)	
		e->cam.position = vecsum(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){0, 1, 0}));
	else if (key == SDLK_RCTRL)
		e->cam.position = vecsub(e->cam.position,
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
	if (key == SDLK_s)
		save_image(env->sdl.image, 0);
	movement(key, env, &redraw);
	rotation(key, env, &redraw);
	if (redraw)
		render(env);
}

