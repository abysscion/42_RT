/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 14:22:30 by cschuste          #+#    #+#             */
/*   Updated: 2019/02/22 16:17:56 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int		intersect_sphere(t_v start, t_v d, t_obj *sph, double *t)
{
	t_v		oc;
	double	k1;
	double	k2;
	double	k3;
	double	discr;

	oc = vecsub(start, sph->pos);
	k1 = vecmult_scal(d, d);
	k2 = 2 * vecmult_scal(oc, d);
	k3 = vecmult_scal(oc, oc) - sph->radius * sph->radius;
	discr = k2 * k2 - 4 * k1 * k3;
	if (discr < 0)
		return (0);
	t[0] = (k2 * -1 + sqrtf(discr)) / (2 * k1);
	t[1] = (k2 * -1 - sqrtf(discr)) / (2 * k1);
	return (1);
}

int		intersect_cylinder(t_v start, t_v d, t_obj *cyl, double *t)
{
	t_v		oc;
	double	k1;
	double	k2;
	double	k3;
	double	discr;

	oc = vecsub(start, cyl->pos);
	cyl->rot = vecnorm(cyl->rot);
	k1 = vecmult_scal(d, d) - pow(vecmult_scal(d, cyl->rot), 2);
	k2 = 2 * (vecmult_scal(oc, d) -
		(vecmult_scal(d, cyl->rot) * vecmult_scal(oc, cyl->rot)));
	k3 = vecmult_scal(oc, oc) - pow(vecmult_scal(oc, cyl->rot), 2) -
			cyl->radius * cyl->radius;
	discr = k2 * k2 - 4 * k1 * k3;
	if (discr < 0)
		return (0);
	t[0] = (k2 * -1 + sqrtf(discr)) / (2 * k1);
	t[1] = (k2 * -1 - sqrtf(discr)) / (2 * k1);
	return (1);
}

int		intersect_cone(t_v start, t_v d, t_obj *cone, double *t)
{
	t_v		oc;
	double	k1;
	double	k2;
	double	k3;
	double	discr;

	oc = vecsub(start, cone->pos);
	cone->rot = vecnorm(cone->rot);
	k1 = vecmult_scal(d, d) - (1 + pow(tan(cone->radius), 2)) *
		pow(vecmult_scal(d, cone->rot), 2);
	k2 = 2 * (vecmult_scal(d, oc) - (1 + pow(tan(cone->radius), 2)) *
		vecmult_scal(d, cone->rot) * vecmult_scal(oc, cone->rot));
	k3 = vecmult_scal(oc, oc) - (1 + pow(tan(cone->radius), 2)) *
		pow(vecmult_scal(oc, cone->rot), 2);
	discr = k2 * k2 - 4 * k1 * k3;
	if (discr < 0)
		return (0);
	t[0] = (k2 * -1 + sqrtf(discr)) / (2 * k1);
	t[1] = (k2 * -1 - sqrtf(discr)) / (2 * k1);
	return (1);
}

int		intersect_plane(t_v start, t_v d, t_obj *plane, double *t)
{
	t[0] = ((vecmult_scal(plane->rot, plane->pos) -
			vecmult_scal(plane->rot, start)) /
			vecmult_scal(plane->rot, d));
	if (t[0] < RAY_LENMIN)
		return (0);
	return (1);
}
