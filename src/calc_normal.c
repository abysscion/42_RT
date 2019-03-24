/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:20:56 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/24 19:16:06 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	cone_normal(t_env *env, double closest, t_surf *cone, t_lc *light)
{
	double	m;
	double	k;

	m = (vecmult_scal(env->ray.dest, cone->orientation) * closest +
		vecmult_scal(vecsub(env->cam.position, cone->position),
		cone->orientation));
	k = tan(cone->radius / 2);
	light->surf_normal = (vecsub(vecsub(light->surf_point, cone->position),
		vecmult_num(vecmult_num(cone->orientation, m), 1 + k * k)));

}

static void	cyl_normal(t_env *env, double closest, t_surf *cyl, t_lc *light)
{
	t_v		surf_to_cam;
	double	m;

	surf_to_cam = vecsub(env->cam.position, cyl->position);
	m = vecmult_scal(env->ray.dest, cyl->orientation) *
		closest + vecmult_scal(surf_to_cam, cyl->orientation);
	light->surf_normal = vecsub(vecsub(light->surf_point, cyl->position),
						vecmult_num(cyl->orientation, m));
}

void		calc_surf_normal(t_env *env, double closest,
							t_lst *surface, t_lc *light)
{
	if (surface->type == T_SPHERE)
		light->surf_normal = vecsub(light->surf_point,
							((t_surf *)surface->obj)->position);
	else if (surface->type == T_PLANE)
		light->surf_normal = ((t_surf *)surface->obj)->orientation;
	else if (surface->type == T_CYLINDER)
		cyl_normal(env, closest, surface->obj, light);
	else if (surface->type == T_CONE)
		cone_normal(env, closest, surface->obj, light);
	light->surf_normal = vecnorm(light->surf_normal);
	if (vecmult_scal(vecnorm(light->orig_dest), light->surf_normal) > 0)
		light->surf_normal = vecmult_num(light->surf_normal, -1);
}
