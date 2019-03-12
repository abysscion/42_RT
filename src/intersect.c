/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 14:22:30 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/11 17:17:38 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		intersect_sphere(t_v start, t_v dest, t_surf *sph, double *roots)
{
	t_v		pos_to_start;
	double	a;
	double	b;
	double	c;
	double	discr;

	pos_to_start = vecsub(start, sph->position);
	a = vecmult_scal(dest, dest);
	b = 2 * vecmult_scal(pos_to_start, dest);
	c = vecmult_scal(pos_to_start, pos_to_start)
		- sph->radius * sph->radius;
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	roots[0] = (b * -1 + sqrt(discr)) / (2 * a);
	roots[1] = (b * -1 - sqrt(discr)) / (2 * a);
	return (1);
}

int		intersect_cylinder(t_v start, t_v dest, t_surf *cyl, double *roots)
{
	t_v		pos_to_start;
	double	a;
	double	b;
	double	c;
	double	discr;

	pos_to_start = vecsub(start, cyl->position);
	cyl->orientation = vecnorm(cyl->orientation);
	a = vecmult_scal(dest, dest) -
		pow(vecmult_scal(dest, cyl->orientation), 2);
	b = 2 * (vecmult_scal(pos_to_start, dest) -
		(vecmult_scal(dest, cyl->orientation) *
		vecmult_scal(pos_to_start, cyl->orientation)));
	c = vecmult_scal(pos_to_start, pos_to_start) -
		pow(vecmult_scal(pos_to_start, cyl->orientation), 2) -
		cyl->radius * cyl->radius;
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	roots[0] = (b * -1 + sqrt(discr)) / (2 * a);
	roots[1] = (b * -1 - sqrt(discr)) / (2 * a);
	return (1);
}

int		intersect_cone(t_v start, t_v dest, t_surf *cone, double *roots)
{
	t_v		pos_to_start;
	double  a;
	double	b;
	double	c;
	double	discr;

	pos_to_start = vecsub(start, cone->position);
	cone->orientation = vecnorm(cone->orientation);
	a = vecmult_scal(dest, dest) - (1 + pow(tan(cone->radius), 2)) *
		pow(vecmult_scal(dest, cone->orientation), 2);
	b = 2 * (vecmult_scal(dest, pos_to_start) -
		(1 + pow(tan(cone->radius), 2)) *
		vecmult_scal(dest, cone->orientation) *
		vecmult_scal(pos_to_start, cone->orientation));
	c = vecmult_scal(pos_to_start, pos_to_start) -
		(1 + pow(tan(cone->radius), 2)) *
		pow(vecmult_scal(pos_to_start, cone->orientation), 2);
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	roots[0] = (b * -1 + sqrt(discr)) / (2 * a);
	roots[1] = (b * -1 - sqrt(discr)) / (2 * a);
	return (1);
}

int		intersect_plane(t_v start, t_v dest, t_surf *plane, double *roots)
{
	roots[0] = ((vecmult_scal(plane->orientation, plane->position) -
			vecmult_scal(plane->orientation, start)) /
			vecmult_scal(plane->orientation, dest));
	roots[1] = +INFINITY;
	if (roots[0] < RAY_LENMIN)
		return (0);
	return (1);
}
