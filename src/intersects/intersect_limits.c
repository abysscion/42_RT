/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_limits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 14:08:27 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/14 16:21:09 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_conic_root(t_surf *surf, t_v *dest, t_v *start, double *root)
{
	double	angle;
	t_v		position_to_point;
	t_v		surf_point;
	double	check;

	surf_point = vecsum(vecmult_num(*dest, *root), *start);
	position_to_point = (vecsub(surf_point, surf->position));
	angle = vecmult_scal(vecnorm(position_to_point), surf->orientation);
	check = (veclen(position_to_point) * angle);
	if (angle < 0 || check > surf->limits.max_height || check < surf->limits.min_height)
		return (0);
	return (1);
}

int		 	limit_conic(t_surf *surf, t_v *dest, t_v *start, double *roots)
{
	double	*min_r;
	double	*max_r;

	min_r = min_root(roots);
	max_r = max_root(roots);
	if (*min_r < RAY_LENMIN)
		return (check_conic_root(surf, dest, start, max_r));
	if (check_conic_root(surf, dest, start, min_r))
		return (1);
	if (check_conic_root(surf, dest, start, max_r))
	{
		*min_r = +INFINITY;
		return (1);
	}
	return (0);

}

static int	check_sphere_root(t_surf *surf, t_v *dest, t_v *start, double *root)
{
	t_v		surf_point;
	t_v		center_to_point;
	double	len;
	double	angle;

	surf_point = vecsum(vecmult_num(*dest, *root), *start);
	center_to_point = vecsub(surf_point, surf->position);
	angle = vecmult_scal(vecnorm(center_to_point), surf->orientation);
	len = veclen(center_to_point) * angle;
	if ((angle == 0) || (angle > 0 && len < surf->limits.max_height) ||
		(angle < 0 && len > surf->limits.min_height))
		return (1);
	return (0);
}

int			limit_sphere(t_surf *surf, t_v *dest, t_v *start, double *roots)
{
	double	*min_r;
	double	*max_r;

	min_r = min_root(roots);
	max_r = max_root(roots);
	if (*min_r < RAY_LENMIN)
		return (check_sphere_root(surf, dest, start, max_r));
	if (check_sphere_root(surf, dest, start, min_r))
		return (1);
	if (check_sphere_root(surf, dest, start, max_r))
	{
		*min_r = +INFINITY;
		return (1);
	}
	return (0);

}

/*LEGACY CODE*/
/*
static int		limit_sphere_max(t_surf *surf, t_v dest, t_v start, double *roots)
{
	t_v		surf_point;
	t_v		center_to_point;
	double	len;
	double	angle;

	surf_point = vecsum(vecmult_num(dest, *max_root(roots)), start);
	center_to_point = vecsub(surf_point, surf->position);
	angle = vecmult_scal(vecnorm(center_to_point), surf->orientation);
	len = veclen(center_to_point) * angle;
	if ((angle == 0) || (angle > 0 && len < surf->limits.max_height) ||
		(angle < 0 && len > surf->limits.min_height))
	{
		*min_root(roots) = +INFINITY;
		return (1);
	}
	return (0);
}

int		limit_sphere(t_surf *surf, t_v dest, t_v start, double *roots)
{
	t_v		surf_point;
	t_v		center_to_point;
	double	len;
	double	angle;

	if (*min_root(roots) < RAY_LENMIN)
		return (limit_sphere_max(surf, dest, start, roots));
	surf_point = vecsum(vecmult_num(dest, *min_root(roots)), start);
	center_to_point = vecsub(surf_point, surf->position);
	angle = vecmult_scal(vecnorm(center_to_point), surf->orientation);
	len = veclen(center_to_point) * angle;
	if ((angle == 0) || (angle > 0 && len < surf->limits.max_height) ||
		(angle < 0 && len > surf->limits.min_height))
		return (1);
	return (limit_sphere_max(surf, dest, start, roots));
}

int		check_max_root(t_surf *surf, t_v dest, t_v start, double *roots)
{
	double	*root;
	double	angle;
	t_v		position_to_point;
	t_v		surf_point;
	double	check;

	root = max_root(roots);
	surf_point = vecsum(vecmult_num(dest, *root), start);
	position_to_point = (vecsub(surf_point, surf->position));
	angle = vecmult_scal(vecnorm(position_to_point), surf->orientation);
	check = (veclen(position_to_point) * angle);
	if (angle < 0 || check > surf->limits.max_height || check < surf->limits.min_height)
		return (0);
	root = min_root(roots);
	*root = +INFINITY;
	return (1);
}

int		limit_cone_cyl(t_surf *surf, t_v dest, t_v start, double *roots)
{	
	double	*root;
	double	angle;
	double	check;
	t_v		position_to_point;
	t_v		surf_point;

	if (*(root = min_root(roots)) < RAY_LENMIN)
		return (check_max_root(surf, dest, start, roots));
	root = min_root(roots);
	surf_point = vecsum(vecmult_num(dest, *root), start);
	position_to_point = (vecsub(surf_point, surf->position));
	angle = vecmult_scal(vecnorm(position_to_point), surf->orientation);
	check = (veclen(position_to_point) * angle);
	if (angle < 0 || check > surf->limits.max_height || check < surf->limits.min_height)
		return (check_max_root(surf, dest, start, roots));
	return (1);
} 
*/