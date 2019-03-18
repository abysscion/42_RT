/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 05:21:02 by emayert           #+#    #+#             */
/*   Updated: 2019/03/18 15:40:45 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*int	expose_hook(t_env *e)
{
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->cam->ptr_vp, 0, 0);
	e->need_regui = 1;
	draw_gui(e);
	return (0);
}

int	mouse_press(int key, int x, int y, t_env *e)
{
	if (!handle_gui_click(x, y, e))
	{
		x -= WIN_W / 2;
		y -= WIN_H / 2;
		if (key == M_LMB)
		{
			if (x < WIN_W / 2 && y < WIN_H / 2)
			{
				rayhit_obj(vp_to_global((t_v) {x, y, 0}), e);
				if (e->hitobj->ishit == 1)
				{
					e->buttons[GUI_BT_CAM]->state = 0;
					e->buttons[GUI_BT_CUBE]->state = 1;
					e->need_regui = 1;
					print_info_about_hitobj(e);
				}
			}
		}
	}
	e->mouse_pressed = 1;
	draw_gui(e);
	return (0);
}

int	mouse_release(int key, int x, int y, t_env *e)
{
	int	i;

	x -= WIN_W / 2;
	y -= WIN_H / 2;
	if (key)
	{;}
	i = GUI_BT_AL - 1;
	while (++i <= GUI_BT_AD)
		if (e->buttons[i]->state == 1)
		{
			e->buttons[i]->state = 0;
			e->need_regui = 1;
		}
	e->mouse_pressed = 0;
	draw_gui(e);
	return (0);
}

int	mouse_move(int x, int y, t_env *e)
{
	x -= WIN_W / 2;
	y -= WIN_H / 2;
	if (e->win)
		{};
	return (0);
} */

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

