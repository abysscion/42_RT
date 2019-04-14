/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_local_coords.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:59:38 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/14 20:39:15 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	calc_conic_local_coords(t_v *surf_p, t_surf *surface,
			double *u, double *v)
{
	t_v		surf_point;
	t_v		center_to_point;
	t_v		sr_pt_base;
	double	cen_to_p_len;
	double	angle;

	surf_point = vecsub(*surf_p,
		vecmult_num(surface->orientation, surface->limits.min_height));
	center_to_point = vecsub(surf_point, surface->position);
	cen_to_p_len = veclen(center_to_point);
	angle = vecmult_scal(vecnorm(center_to_point), surface->basis.y);
	*v = angle * cen_to_p_len;
	sr_pt_base = vecsub(surf_point, vecmult_num(surface->basis.y, *v));
	center_to_point = vecnorm(vecsub(sr_pt_base, surface->position));
	angle = vecmult_scal(center_to_point, surface->basis.x);
	if (vecmult_scal(vecmult_vec(surface->basis.x, surface->basis.y),
		center_to_point) > 0)
		*u = acos(vecmult_scal(center_to_point, surface->basis.x)) / (2 * M_PI);
	else
	{
		*u = (acos(vecmult_scal(center_to_point, surface->basis.x)) + M_PI)
			/ (2 * M_PI);
		*u = fabs(*u - 1) + 0.5;
	}
	*v = *v / (surface->limits.max_height - surface->limits.min_height);
}

void	calc_sphere_local_coords(t_v *surf_point, t_surf *surface,
			double *u, double *v)
{
	t_v		center_to_point;
	double	phi;
	double	theta;

	center_to_point = vecnorm(vecsub(*surf_point, surface->position));
	phi = acos(vecmult_scal(surface->basis.y, center_to_point));
	*v = phi / M_PI;
	theta = (acos(vecmult_scal(center_to_point, surface->basis.x) / sin(phi)))
		/ (2 * M_PI);
	if (vecmult_scal(vecmult_vec(surface->basis.x, surface->basis.y),
		center_to_point) > 0)
		*u = theta;
	else
		*u = 1 - theta;
}

void	calc_plane_local_coords(t_v *surf_point, t_surf *surface,
			double *u, double *v)
{
	t_basis	*basis;

	basis = &surface->basis;
	*u = basis->x.x * surf_point->x + basis->x.y * surf_point->y +
				basis->x.z * surf_point->z;
	*v = basis->y.x * surf_point->x + basis->y.y * surf_point->y +
				basis->y.z * surf_point->z;
}
