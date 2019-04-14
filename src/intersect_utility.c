/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 14:08:27 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/13 19:45:35 by eloren-l         ###   ########.fr       */
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

// PLANES BECOME BIGGER WHEN THEY ARE ROTATED - 45 deg rotations give max size increase (bug)

// DISC CAN BE MADE THE SAME WAY AS A PLANE BUT CALCULATIONS ARE DIFFERENT - YOU NEED TO 
// CALC X-Y (SQRT(x^2 + y^2)) RADIUS AND COMPARE TO MAX RADIUS INSTEAD OF CHECKING BORDERS
// IN THAT SENSE DISC IS THE SAME AS PLANE BUT DIFFERENT WAY TO CALCULATE BOUNDARIES
// NEED TO REFACTOR ALL OF THE INTERSECTION CODE AND PUT IT INTO DIFFERENT FOLDER!

int		limit_plane(t_surf *surf, t_v dest, t_v start, double *roots)
{
	t_v		adjusted_surf_point;
	double	adj_x;
	double	adj_y;
	double	width;
	double	height;

	width = (surf->limits.max_width - surf->limits.min_width) / 2;
	height = (surf->limits.max_height - surf->limits.min_height) / 2;
	if (width < 0 || height < 0)
		return (0);
	adjusted_surf_point = vecsum(vecmult_num(dest, *(min_root(roots))), start);
	adjusted_surf_point = vecsub(adjusted_surf_point, surf->position);
	calc_plane_local_coords(&adjusted_surf_point, surf, &adj_x, &adj_y);
	if (adj_x > -width && adj_x < width && adj_y > -height && adj_y < height)
		return (1);
	return (0);
}

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

	surf_point = vecsum(vecmult_num(dest, *min_root(roots)), start);
	center_to_point = vecsub(surf_point, surf->position);
	angle = vecmult_scal(vecnorm(center_to_point), surf->orientation);
	len = veclen(center_to_point) * angle;
	if ((angle == 0) || (angle > 0 && len < surf->limits.max_height) ||
		(angle < 0 && len > surf->limits.min_height))
		return (1);
	return (limit_sphere_max(surf, dest, start, roots));
}