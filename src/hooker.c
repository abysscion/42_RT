/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 05:21:02 by emayert           #+#    #+#             */
/*   Updated: 2019/03/12 12:54:45 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

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

static	void	key_handler2(int key, t_env *e)
{
	if (key == K_NUM_4 || key == 0)
		e->cam.rotation.y -= M_PI / 180 * ROT_STEP;
	else if (key == K_NUM_6 || key == 2)
		e->cam.rotation.y += M_PI / 180 * ROT_STEP;
	else if (key == K_NUM_2 || key == 1)
		e->cam.rotation.x -= M_PI / 180 * ROT_STEP;
	else if (key == K_NUM_8 || key == 13)
		e->cam.rotation.x += M_PI / 180 * ROT_STEP;
}

void			key_handler(int key, t_env *e)
{
	if (key == K_ARRUP || key == K_ARRDOWN  || key == K_ARRLEFT ||
	key == K_ARRRIGHT || key == K_NUM_PLUS || key == K_NUM_MINUS ||
	key == K_NUM_2 || key == K_NUM_4 || key == K_NUM_6 || key == K_NUM_8)
		e->need_rerender = 1;
	if (key == K_ARRUP)
		e->cam.position = vecsub(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){0, 1, 0}));
	else if (key == K_ARRDOWN)
		e->cam.position = vecsum(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){0, 1, 0}));
	else if (key == K_ARRLEFT)
		e->cam.position = vecsub(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){1, 0, 0}));
	else if (key == K_ARRRIGHT)
		e->cam.position = vecsum(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){1, 0, 0}));
	else if (key == K_NUM_PLUS || key == 24)
		e->cam.position = vecsum(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){0, 0, 1}));
	else if (key == K_NUM_MINUS || key == 27)
		e->cam.position = vecsub(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){0, 0, 1}));
	else
		key_handler2(key, e);
}


int	key_hook(int key, t_env *e)
{
	if (key == K_ESC)
		exit(0);
	key_handler(key, e);
	render(e);
	return (0);
}

