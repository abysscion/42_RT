/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_limits_flat.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 16:01:06 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/14 20:52:37 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		limit_plane(t_surf *surf, t_v *dest, t_v *start, double *roots)
{
	t_v		adjusted_surf_point;
	double	adj_x;
	double	adj_y;
	double	width;
	double	height;

	width = surf->limits.max_width / 2;
	height = surf->limits.max_height / 2;
	if (width <= 0 || height <= 0)
		return (0);
	adjusted_surf_point = vecsum(vecmult_num(*dest, *(min_root(roots))),
		*start);
	adjusted_surf_point = vecsub(adjusted_surf_point, surf->position);
	calc_plane_local_coords(&adjusted_surf_point, surf, &adj_x, &adj_y);
	if (adj_x > -width && adj_x < width && adj_y > -height && adj_y < height)
		return (1);
	return (0);
}

int		limit_disc(t_surf *surf, t_v *dest, t_v *start, double *roots)
{
	t_v		adjusted_surf_point;
	double	adj_x;
	double	adj_y;

	if (surf->radius <= 0)
		return (0);
	adjusted_surf_point = vecsum(vecmult_num(*dest, *(min_root(roots))),
		*start);
	adjusted_surf_point = vecsub(adjusted_surf_point, surf->position);
	calc_plane_local_coords(&adjusted_surf_point, surf, &adj_x, &adj_y);
	if (sqrt(adj_x * adj_x + adj_y * adj_y) < surf->radius)
		return (1);
	return (0);
}
