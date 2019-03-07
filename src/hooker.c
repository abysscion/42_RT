/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 05:21:02 by emayert           #+#    #+#             */
/*   Updated: 2019/03/07 09:46:09 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int	expose_hook(t_env *e)
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
}

int	key_hook(int key, t_env *e)
{
	if (key == K_ESC)
		exit(0);
	if (e->hitobj->ishit == -1)
		key_handler(key, e);
	else
	{
		if (key == K_ARRRIGHT)
			translate_obj(&e->objs->objarr[e->hitobj->index]->pos.x, 1, 1, e);
		else if (key == K_ARRLEFT)
			translate_obj(&e->objs->objarr[e->hitobj->index]->pos.x, -1, 1, e);
		else if (key == K_ARRUP)
			translate_obj(&e->objs->objarr[e->hitobj->index]->pos.y, -1, 1, e);
		else if (key == K_ARRDOWN)
			translate_obj(&e->objs->objarr[e->hitobj->index]->pos.y, 1, 1, e);
		else if (key == K_NUM_PLUS)
			translate_obj(&e->objs->objarr[e->hitobj->index]->pos.z, 1, 1, e);
		else if (key == K_NUM_MINUS)
			translate_obj(&e->objs->objarr[e->hitobj->index]->pos.z, -1, 1, e);
		e->need_regui = 1;
	}
	draw_gui(e);
	render(e);
	return (0);
}
