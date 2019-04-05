/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:20:56 by cschuste          #+#    #+#             */
/*   Updated: 2019/04/05 13:12:44 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parab_normal(t_surf *parab, t_lc *light)
{
	double	m;
	t_v 	cp;

	cp = vecsub(light->surf_point, parab->position);
	m = vecmult_scal(parab->orientation, cp);
	light->surf_normal = vecsub(cp, vecmult_num(parab->orientation,
		m + parab->radius));
}

static void	cone_normal(t_env *env, double closest, t_surf *cone, t_lc *light)
{
	double	m;
	double	k;

	m = (vecmult_scal(env->ray.dest, cone->orientation) * closest +
		vecmult_scal(vecsub(env->cam.position, cone->position),
		cone->orientation));
	k = tan(cone->radius);
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
	else if (surface->type == T_PARAB)
		parab_normal(surface->obj, light);
	light->surf_normal = vecnorm(light->surf_normal);
}
