/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:20:56 by cschuste          #+#    #+#             */
/*   Updated: 2019/02/22 15:54:29 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_v				normal2cone(t_env *e, t_v dest, double closest, int i)
{
	t_v		p;
	t_v		v;
	t_v		c;
	double	m;
	double	k;

	p = vecsum(e->cam->pos, vecmult_num(dest, closest));
	v = e->objs->objarr[i]->rot;
	c = e->objs->objarr[i]->pos;
	m = (vecmult_scal(dest, v) * closest + vecmult_scal(vecsub(e->cam->pos,
			e->objs->objarr[i]->pos), v));
	k = tan(e->objs->objarr[i]->radius / 2);
	return (vecsub(vecsub(p, c), vecmult_num(vecmult_num(v, m), 1 + k * k)));
}

t_v				normal2cyl(t_env *e, t_v dest, double closest, int i)
{
	t_v		p;
	t_v		v;
	t_v		c;
	t_v		x;
	double	m;

	p = vecsum(e->cam->pos, vecmult_num(dest, closest));
	x = vecsub(e->cam->pos, e->objs->objarr[i]->pos);
	v = e->objs->objarr[i]->rot;
	c = e->objs->objarr[i]->pos;
	m = vecmult_scal(dest, v) * closest + vecmult_scal(x, v);
	return (vecsub(vecsub(p, c), vecmult_num(v, m)));
}

t_v				normal2plane(t_env *e, int i)
{
	return ((t_v) {e->objs->objarr[i]->rot.x, e->objs->objarr[i]->rot.y,
						e->objs->objarr[i]->rot.z});
}
