/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 14:22:30 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/07 14:21:48 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	abc[0] = a, abc[1] = b, abc[2] = c in ax^2 + bx^2 + c = 0
*/

int		intersect_sphere(t_v start, t_v dest, t_obj *sph, double *roots)
{
	t_v		oc;
	double	abc[3];

	oc = vecsub(start, sph->pos);
	abc[0] = vecmult_scal(dest, dest);
	abc[1] = 2 * vecmult_scal(oc, dest);
	abc[2] = vecmult_scal(oc, oc) - sph->radius * sph->radius;
	return (solve_quadratic(&abc[0], roots));
}

int		intersect_cylinder(t_v start, t_v dest, t_obj *cyl, double *roots)
{
	t_v		oc;
	double	abc[3];

	oc = vecsub(start, cyl->pos);
	cyl->rot = vecnorm(cyl->rot);
	abc[0] = vecmult_scal(dest, dest) - pow(vecmult_scal(dest, cyl->rot), 2);
	abc[1] = 2 * (vecmult_scal(oc, dest) -
		(vecmult_scal(dest, cyl->rot) * vecmult_scal(oc, cyl->rot)));
	abc[2] = vecmult_scal(oc, oc) - pow(vecmult_scal(oc, cyl->rot), 2) -
			cyl->radius * cyl->radius;
	return (solve_quadratic(&abc[0], roots));
}

int		intersect_cone(t_v start, t_v dest, t_obj *cone, double *roots)
{
	t_v		oc;
	double	abc[0];

	oc = vecsub(start, cone->pos);
	cone->rot = vecnorm(cone->rot);
	abc[0] = vecmult_scal(dest, dest) - (1 + pow(tan(cone->radius), 2)) *
		pow(vecmult_scal(dest, cone->rot), 2);
	abc[1] = 2 * (vecmult_scal(dest, oc) - (1 + pow(tan(cone->radius), 2)) *
		vecmult_scal(dest, cone->rot) * vecmult_scal(oc, cone->rot));
	abc[2] = vecmult_scal(oc, oc) - (1 + pow(tan(cone->radius), 2)) *
		pow(vecmult_scal(oc, cone->rot), 2);	
	return (solve_quadratic(&abc[0], roots));
}

int		intersect_plane(t_v start, t_v dest, t_obj *plane, double *t)
{
	t[0] = ((vecmult_scal(plane->rot, plane->pos) -
			vecmult_scal(plane->rot, start)) /
			vecmult_scal(plane->rot, dest));
	t[1] = INFINITY;
	if (t[0] < RAY_LENMIN)
		return (0);
	return (1);
}

/*
** returns 1 if there are real solutions, returns 0 if there are none
*/

int		solve_quadratic(double *abc, double *roots)
{
	double discr;

	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discr < 0)
		return (0);
	roots[0] = (abc[1] * -1 + sqrtf(discr)) / (2 * abc[0]);
	roots[1] = (abc[1] * -1 - sqrtf(discr)) / (2 * abc[0]);
	return (1);
}