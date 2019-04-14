/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 21:03:53 by cschuste          #+#    #+#             */
/*   Updated: 2019/04/14 20:08:13 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	calc_spec(t_lc *lc, t_surf *surface, t_light *light)
{
	double	cosine;

	lc->reflect_dir = calc_reflected_ray(lc->point_to_light, lc->surf_normal);
	cosine = vecmult_scal(lc->reflect_dir, lc->to_start);
	if (cosine > 0)
		return (light->intensity * pow(cosine / (veclen(lc->reflect_dir) *
				veclen(lc->to_start)), surface->specular));
	else
		return (0);
}

static void		choose_light(t_env *env, t_lc *lc, t_lst *light)
{
	if (light->type == T_POINT)
	{
		env->ray.min = RAY_LENMIN;
		env->ray.max = 1;
		lc->point_to_light = vecsub(((t_light *)light->obj)->position,
							lc->surf_point);
	}
	else if (light->type == T_DIRECTIONAL)
	{
		env->ray.min = RAY_LENMIN;
		env->ray.max = RAY_LENMAX;
		lc->point_to_light = ((t_light *)light->obj)->position;
	}
	env->ray.dest = lc->point_to_light;
	env->ray.start = lc->surf_point;
}

static void		calc_light(t_env *env, t_surf *surface,
								double *intens, t_lc *lc)
{
	double	cosine;
	t_lst	*light;

	light = env->lights;
	while (light)
	{
		if (light->type == T_AMBIENT)
			*intens += ((t_light *)light->obj)->intensity;
		else
		{
			choose_light(env, lc, light);
			if (closest_intersection(env, NULL) >= env->ray.max)
			{
				if (vecmult_scal(lc->surf_normal, vecnorm(lc->to_start)) < 0)
					lc->surf_normal = vecmult_num(lc->surf_normal, -1);
				cosine = vecmult_scal(lc->surf_normal,
					vecnorm(lc->point_to_light));
				if (cosine > 0)
					*intens += ((t_light *)light->obj)->intensity * cosine;
				if (surface->specular > 0 && cosine > 0)
					*intens += calc_spec(lc, surface, light->obj);
			}
		}
		light = light->next;
	}
}

t_clr			light_on(t_env *env, double closest, t_surf *surface, int rec)
{
	t_lc				lc;
	double				intensity;
	t_clr				color;
	t_clr				ref_color;

	lc.orig_dest = env->ray.dest;
	lc.to_start = vecmult_num(env->ray.dest, -1);
	lc.surf_point = vecsum(env->ray.start,
		vecmult_num(env->ray.dest, closest));
	if (surface->normal_map != NULL)
		get_texture_normal(surface, &lc);
	else
		calc_surf_normal(env, closest, surface, &lc);
	lc.orig_norm = lc.surf_normal;
	intensity = 0;
	calc_light(env, surface, &intensity, &lc);
	if (surface->texture)
		get_texture_color(surface, &lc);
	calc_color(&color, intensity, surface);
	if (rec > 0 && surface->reflect > 0)
	{
		env->ray.start = lc.surf_point;
		env->ray.dest = calc_reflected_ray(lc.to_start, lc.surf_normal);
		env->ray.min = RAY_LENMIN;
		env->ray.max = RAY_LENMAX;
		ref_color = trace_ray(env, rec - 1);
		calc_ref_color(&color, &ref_color, surface);
	}
	else if (surface->transp > 0 && rec > 0)
		color = calc_refract(env, lc, surface, rec);
	return (color);
}
                                                