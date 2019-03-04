/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 05:21:02 by emayert           #+#    #+#             */
/*   Updated: 2019/03/04 12:50:27 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int	expose_hook(t_env *e)
{
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->cam->ptr_vp, 0, 0);
	draw_gui(e);
	return (0);
}

int	mouse_press(int key, int x, int y, t_env *e)
{
	if (!handle_gui_click(x, y, e))
	{
	// x -= WIN_W / 2;
	// y -= WIN_H / 2;
	// if (key == M_LMB)
	// {
	// 	if (x < WIN_W / 2 && y < WIN_H / 2)
	// 	{
	// 		rayhit_obj(vp_to_global((t_v) {x, y, 0}), e);
	// 		if (e->hitobj->ishit)
	// 			print_info_about_hitobj(e);
	// 	}
	// }
	// if (key == M_RMB)
	// 	e->hitobj->ishit = -1;
	}
	e->mouse_pressed = 1;
	return (0);
}

int	mouse_release(int key, int x, int y, t_env *e)
{
	x -= WIN_W / 2;
	y -= WIN_H / 2;
	if (e->win)
		{};
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
	// if (e->hitobj->ishit == -1)
	// 	key_handler(key, e);
	// else
	// {
	// 	if (key == K_ARRRIGHT)
	// 		e->objs->objarr[e->hitobj->index]->pos.x += 1;
	// 	else if (key == K_ARRLEFT)
	// 		e->objs->objarr[e->hitobj->index]->pos.x -= 1;
	// 	else if (key == K_ARRUP)
	// 		e->objs->objarr[e->hitobj->index]->pos.y -= 1;
	// 	else if (key == K_ARRDOWN)
	// 		e->objs->objarr[e->hitobj->index]->pos.y += 1;
	// 	else if (key == K_NUM_PLUS)
	// 		e->objs->objarr[e->hitobj->index]->pos.z += 1;
	// 	else if (key == K_NUM_MINUS)
	// 		e->objs->objarr[e->hitobj->index]->pos.z -= 1;
	// }
	// render(e);
	return (0);
}
