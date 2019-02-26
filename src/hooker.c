/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <emayert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 05:21:02 by emayert           #+#    #+#             */
/*   Updated: 2019/02/23 17:07:21 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int	expose_hook(t_env *e)
{
	render(e);
	return (0);
}

int	mouse_press(int key, int x, int y, t_env *e)
{
	x -= WIN_W / 2;
	y -= WIN_H / 2;
	if (key == M_LMB)
	{
		rayhit_obj(vp_to_global((t_v) {x, y, 0}), e);
		if (e->hitobj->ishit)
			print_info_about_hitobj(e);
	}
	if (key == M_RMB)
		e->hitobj->ishit = -1;
	e->mouse_pressed = 1;
	return (0);
}

int	mouse_release(int key, int x, int y, t_env *e)
{
	x -= WIN_W / 2;
	y -= WIN_H / 2;
	++key;
	e->mouse_pressed = 0;
	return (0);
}

int	mouse_move(int x, int y, t_env *e)
{
	x -= WIN_W / 2;
	y -= WIN_H / 2;
	return (0);
}

int	key_hook(int key, t_env *e)
{
	if (e->hitobj->ishit == -1)
		key_handler(key, e);
	else
	{
		if (key == K_ARRIGHT)
			e->objs->objarr[e->hitobj->index]->pos.x += 1;
		else if (key == K_ARRLEFT)
			e->objs->objarr[e->hitobj->index]->pos.x -= 1;
		else if (key == K_ARRUP)
			e->objs->objarr[e->hitobj->index]->pos.y -= 1;
		else if (key == K_ARRDOWN)
			e->objs->objarr[e->hitobj->index]->pos.y += 1;
		else if (key == K_NUM_PLUS)
			e->objs->objarr[e->hitobj->index]->pos.z += 1;
		else if (key == K_NUM_MINUS)
			e->objs->objarr[e->hitobj->index]->pos.z -= 1;
	}
	render(e);
	return (0);
}
