/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_conic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 19:39:29 by cschuste          #+#    #+#             */
/*   Updated: 2019/04/17 19:39:30 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		intersect_cylinder(t_v *start, t_v *dest, t_surf *cyl, double *roots)
{
	t_v		pos_to_start;
	double	a;
	double	b;
	double	c;
	double	discr;

	pos_to_start = vecsub(*start, cyl->position);
	cyl->rotation = vecnorm(cyl->rotation);
	a = vecmult_scal(*dest, *dest) -
		pow(vecmult_scal(*dest, cyl->rotation), 2);
	b = 2 * (vecmult_scal(pos_to_start, *dest) -
		(vecmult_scal(*dest, cyl->rotation) *
		vecmult_scal(pos_to_start, cyl->rotation)));
	c = vecmult_scal(pos_to_start, pos_to_start) -
		pow(vecmult_scal(pos_to_start, cyl->rotation), 2) -
		cyl->radius * cyl->radius;
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	roots[0] = (b * -1 + sqrt(discr)) / (2 * a);
	roots[1] = (b * -1 - sqrt(discr)) / (2 * a);
	return (limit_conic(cyl, dest, start, roots));
}

int		intersect_cone(t_v *start, t_v *dest, t_surf *cone, double *roots)
{
	t_v		pos_to_start;
	double	a;
	double	b;
	double	c;
	double	discr;

	pos_to_start = vecsub(*start, cone->position);
	cone->rotation = vecnorm(cone->rotation);
	a = vecmult_scal(*dest, *dest) - (1 + pow(tan(cone->radius), 2)) *
		pow(vecmult_scal(*dest, cone->rotation), 2);
	b = 2 * (vecmult_scal(*dest, pos_to_start) -
		(1 + pow(tan(cone->radius), 2)) *
		vecmult_scal(*dest, cone->rotation) *
		vecmult_scal(pos_to_start, cone->rotation));
	c = vecmult_scal(pos_to_start, pos_to_start) -
		(1 + pow(tan(cone->radius), 2)) *
		pow(vecmult_scal(pos_to_start, cone->rotation), 2);
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	roots[0] = (b * -1 + sqrt(discr)) / (2 * a);
	roots[1] = (b * -1 - sqrt(discr)) / (2 * a);
	return (limit_conic(cone, dest, start, roots));
}

int		intersect_paraboloid(t_v *start, t_v *dest, t_surf *parab,
			double *roots)
{
	t_v		pos_to_start;
	double	a;
	double	b;
	double	c;
	double	discr;

	pos_to_start = vecsub(*start, parab->position);
	parab->rotation = vecnorm(parab->rotation);
	a = vecmult_scal(*dest, *dest) -
		pow(vecmult_scal(*dest, parab->rotation), 2);
	b = vecmult_scal(*dest, parab->rotation) * (vecmult_scal(pos_to_start,
		parab->rotation) + 2 * parab->radius);
	b = 2 * (vecmult_scal(*dest, pos_to_start) - b);
	c = vecmult_scal(pos_to_start, parab->rotation) *
		(vecmult_scal(pos_to_start, parab->rotation) + 4 * parab->radius);
	c = vecmult_scal(pos_to_start, pos_to_start) - c;
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	roots[0] = (b * -1 + sqrt(discr)) / (2 * a);
	roots[1] = (b * -1 - sqrt(discr)) / (2 * a);
	return (limit_conic(parab, dest, start, roots));
}
