/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supply.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 01:23:45 by emayert           #+#    #+#             */
/*   Updated: 2019/03/07 09:35:04 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

/*
**	Puts pixel on image at (x, y) windows coordinates with taken color.
*/

void	ppx_on_img(int y, int x, int color, t_env *e)
{
	y += WIN_H / 2;
	x += WIN_W / 2;
	e->cam->view_port_addr[WIN_W * y + x] = color;
}

/*
**	Translates object using it's pos->(val) to change it by (add).
**	Parameter (rd) needed for possibility of translating without
**		immediate full picture rerender.
*/

void	translate_obj(double *val, double add, int rd, t_env *e)
{
	*val += add;
	if (rd == 1)
		e->need_rerender = 1;
}

t_v		vp_to_global(t_v vp_p)
{
	t_v ret;

	ret.x = vp_p.x * 1 / WIN_W;
	ret.y = vp_p.y * 1 / WIN_H;
	ret.z = 1;
	return (ret);
}

void	light_abuse(int *i, double *intens)
{
	*i = -1;
	*intens = 0.0;
}
