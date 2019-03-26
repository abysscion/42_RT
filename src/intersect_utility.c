/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 14:08:27 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/26 15:07:57 by eloren-l         ###   ########.fr       */
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

/*
** CONE NEED IT'S OWN LIMITS CHECK
** OTHERWISE SHADOWS ARE NOT CALCULATED
** PROPERLY, NO IDEA YET HOW TO DO IT
*/

int		check_max_root(t_surf *surf, t_v dest, t_v start, double *roots)
{
	double	*root;
	double	angle;
	t_v		position_to_point;
	t_v		surf_point;

	root = max_root(roots);
	surf_point = vecsum(vecmult_num(dest, *root), start);
	position_to_point = (vecsub(surf_point, surf->position));
	angle = vecmult_scal(vecnorm(position_to_point), surf->orientation);
	if (angle < 0 || (veclen(position_to_point) * angle) > surf->height)
		return (0);
	root = min_root(roots);
	*root = +INFINITY;
	return (1);
}

int		limit_cone_cyl(t_surf *surf, t_v dest, t_v start, double *roots)
{	
	double	*root;
	double	angle;
	t_v		position_to_point;
	t_v		surf_point;

	if (*(root = min_root(roots)) < RAY_LENMIN)
		return (check_max_root(surf, dest, start, roots));
	root = min_root(roots);
	surf_point = vecsum(vecmult_num(dest, *root), start);
	position_to_point = (vecsub(surf_point, surf->position));
	angle = vecmult_scal(vecnorm(position_to_point), surf->orientation);
	if (angle < 0 || (veclen(position_to_point) * angle) > surf->height)
		return (check_max_root(surf, dest, start, roots));
	return (1);
}
/*int		check_max_root(t_surf *surf, t_v dest, t_v start, double *root)
{
		double	angle;
		t_v		position_to_point;
		t_v		surf_point;

		surf_point = vecsum(vecmult_num(dest, *root), start);
		position_to_point = (vecsub(surf_point, surf->position));
		angle = vecmult_scal(vecnorm(position_to_point), surf->orientation);
		if (angle < 0 || (veclen(position_to_point) * angle) > surf->height)
			return (0);
		return (1);
}

int		limit_cone_cyl(t_surf *surf, t_v dest, t_v start, double *roots)
{	
	int		max_state;
	double	*root;
	double	angle;
	t_v		position_to_point;
	t_v		surf_point;

	if (*(root = min_root(roots)) < RAY_LENMIN &&
		(max_state = check_max_root(surf, dest, start, max_root(roots))) == 1)
		return (1);
	surf_point = vecsum(vecmult_num(dest, *root), start);
	position_to_point = (vecsub(surf_point, surf->position));
	angle = vecmult_scal(vecnorm(position_to_point), surf->orientation);
	if (angle > 0 && (veclen(position_to_point) * angle) < surf->height)
		return (1);
	else if (max_state == 1)
	{
		*root = +INFINITY;
		return (1);
	}
	else
		return (0);
}*/
