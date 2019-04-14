/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_other.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 14:22:30 by cschuste          #+#    #+#             */
/*   Updated: 2019/04/14 16:22:59 by eloren-l         ###   ########.fr       */
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
	return (limit_sphere(sph, &dest, &start, roots));
}

int		intersect_plane(t_v start, t_v dest, t_surf *plane, double *roots)
{
	roots[0] = ((vecmult_scal(plane->orientation, plane->position) -
			vecmult_scal(plane->orientation, start)) /
			vecmult_scal(plane->orientation, dest));
	roots[1] = +INFINITY;
	if (roots[0] < RAY_LENMIN)
		return (0);
	return (limit_plane(plane, &dest, &start, roots));
}
