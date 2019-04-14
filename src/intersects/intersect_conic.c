/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_conic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 15:56:29 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/14 15:59:29 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	return (limit_conic(cyl, &dest, &start, roots));
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
	return (limit_conic(cone, &dest, &start, roots));
}

int		intersect_paraboloid(t_v start, t_v dest, t_surf *parab, double *roots)
{
	t_v		pos_to_start;
	double  a;
	double	b;
	double	c;
	double	discr;

	pos_to_start = vecsub(start, parab->position);
	parab->orientation = vecnorm(parab->orientation);
	a = vecmult_scal(dest, dest) - pow(vecmult_scal(dest, parab->orientation), 2);
	b = vecmult_scal(dest, parab->orientation) * (vecmult_scal(pos_to_start,
		parab->orientation) + 2 * parab->radius);
	b = 2 * (vecmult_scal(dest, pos_to_start) - b);
	c = vecmult_scal(pos_to_start, parab->orientation) *
		(vecmult_scal(pos_to_start, parab->orientation) + 4 * parab->radius);
	c = vecmult_scal(pos_to_start, pos_to_start) - c;
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	roots[0] = (b * -1 + sqrt(discr)) / (2 * a);
	roots[1] = (b * -1 - sqrt(discr)) / (2 * a);
	return (limit_conic(parab, &dest, &start, roots));
}
