/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 14:08:27 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/24 20:47:05 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	*min_root(double *roots)
{
	if (roots[0] > roots[1])
		return (&roots[1]);
	return (&roots[0]);
}

static double	*max_root(double *roots)
{
	if (roots[0] > roots[1])
		return (&roots[0]);
	return (&roots[1]);
}

int		limit_cone_cyl(t_surf *surf, t_v dest, t_v start, double *roots)
{	
	double	*root;
	double	angle;
	t_v		position_to_point;
	t_v		surf_point;

	root = min_root(roots);
	surf_point = vecsum(vecmult_num(dest, *root), start);
	position_to_point = (vecsub(surf_point, surf->position));
	angle = vecmult_scal(vecnorm(position_to_point), surf->orientation);
	if (angle < 0 || (veclen(position_to_point) * angle) > surf->height)
	{
		root = max_root(roots);
		surf_point = vecsum(vecmult_num(dest, *root), start);
		position_to_point = (vecsub(surf_point, surf->position));
		angle = vecmult_scal(vecnorm(position_to_point), surf->orientation);
		if (angle < 0 || (veclen(position_to_point) * angle) > surf->height)
			return (0);
		root = min_root(roots);
		*root = +INFINITY;
	}
	return (1);
}
