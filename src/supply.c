/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supply.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 01:23:45 by emayert           #+#    #+#             */
/*   Updated: 2019/02/22 20:16:15 by cschuste         ###   ########.fr       */
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

t_v		vp_to_global(t_v vp_p)
{
	t_v ret;

	ret.x = vp_p.x * 1 / WIN_W;
	ret.y = vp_p.y * 1 / WIN_H;
	ret.z = 1;
	return (ret);
}

/*
**	Returns vector rotated by radian angles stored in (t_v) a.
*/

t_v		vec_rotate(t_v a, t_v vec)
{
	t_v	retv;
	t_v temp;

	temp = vec;
	retv.x = temp.x;
	retv.y = temp.y * cos(a.x) - temp.z * sin(a.x);
	retv.z = temp.y * sin(a.x) + temp.z * cos(a.x);
	temp = retv;
	retv.x = temp.x * cos(a.y) + temp.z * sin(a.y);
	retv.y = temp.y;
	retv.z = -temp.x * sin(a.y) + temp.z * cos(a.y);
	return (retv);
}

void	light_abuse(int *i, double *intens)
{
	*i = -1;
	*intens = 0.0;
}
