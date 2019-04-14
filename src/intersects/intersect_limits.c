/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_limits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 14:08:27 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/14 20:55:00 by eloren-l         ###   ########.fr       */
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
	if (angle < 0 || check > surf->limits.max_height ||
		check < surf->limits.min_height)
		return (0);
	return (1);
}

int			limit_conic(t_surf *surf, t_v *dest, t_v *start, double *roots)
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
