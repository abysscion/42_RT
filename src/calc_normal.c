/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:20:56 by cschuste          #+#    #+#             */
/*   Updated: 2019/04/16 20:16:37 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parab_normal(t_surf *parab, t_lc *light)
{
	double	m;
	t_v		cp;

	cp = vecsub(light->surf_point, parab->position);
	m = vecmult_scal(parab->rotation, cp);
	light->surf_normal = vecsub(cp, vecmult_num(parab->rotation,
		m + parab->radius));
}

static void	cone_normal(t_env *env, double closest, t_surf *cone, t_lc *light)
{
	double	m;
	double	k;

	m = (vecmult_scal(env->ray.dest, cone->rotation) * closest +
		vecmult_scal(vecsub(env->cam.position, cone->position),
		cone->rotation));
	k = tan(cone->radius);
	light->surf_normal = (vecsub(vecsub(light->surf_point, cone->position),
		vecmult_num(vecmult_num(cone->rotation, m), 1 + k * k)));
}

static void	cyl_normal(t_env *env, double closest, t_surf *cyl, t_lc *light)
{
	t_v		surf_to_cam;
	double	m;

	surf_to_cam = vecsub(env->cam.position, cyl->position);
	m = vecmult_scal(env->ray.dest, cyl->rotation) *
		closest + vecmult_scal(surf_to_cam, cyl->rotation);
	light->surf_normal = vecsub(vecsub(light->surf_point, cyl->position),
						vecmult_num(cyl->rotation, m));
}

void		calc_surf_normal(t_env *env, double closest,
							t_surf *surface, t_lc *light)
{
	if (surface->type == T_SPHERE)
		light->surf_normal = vecsub(light->surf_point,
							surface->position);
	else if (surface->type == T_PLANE || surface->type == T_DISC)
		light->surf_normal = surface->rotation;
	else if (surface->type == T_CYLINDER)
		cyl_normal(env, closest, surface, light);
	else if (surface->type == T_CONE)
		cone_normal(env, closest, surface, light);
	else if (surface->type == T_PARAB)
		parab_normal(surface, light);
	light->surf_normal = vecnorm(light->surf_normal);
}
