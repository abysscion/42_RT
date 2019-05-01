/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon_effect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:52:56 by fdibbert          #+#    #+#             */
/*   Updated: 2019/04/17 20:27:05 by fdibbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		intersect_surface(t_env *env, t_lst *surf_lst,
					t_surf **closest_surf, double *closest_dist)
{
	t_surf	*curr_surf;
	double	roots[2];
	int		intersect;

	curr_surf = (t_surf *)(surf_lst->obj);
	intersect = choose_type(env, surf_lst, roots);
	if (intersect && roots[0] > env->ray.min && roots[0] < *closest_dist)
	{
		*closest_dist = roots[0];
		closest_surf == NULL ? 0 : (*closest_surf = curr_surf);
	}
	if (intersect && roots[1] > env->ray.min && roots[1] < *closest_dist)
	{
		*closest_dist = roots[1];
		closest_surf == NULL ? 0 : (*closest_surf = curr_surf);
	}
}

double			closest_intersect(t_env *env, t_surf **closest_surf)
{
	double	closest_dist;
	t_lst	*objects;
	t_lst	*surface;

	objects = env->objects;
	closest_dist = env->ray.max;
	while (objects)
	{
		surface = ((t_obj *)objects->obj)->surfaces;
		while (surface)
		{
			intersect_surface(env, surface, closest_surf, &closest_dist);
			surface = surface->next;
		}
		objects = objects->next;
	}
	return (closest_dist);
}

t_surf			*trace_object(t_env *env)
{
	double	closest_dist;
	t_surf	*closest_surf;

	closest_surf = NULL;
	closest_dist = closest_intersect(env, &closest_surf);
	if (closest_dist >= env->ray.max)
		return (closest_surf);
	return (closest_surf);
}

void			check_surf(t_surf *surf, t_env *env, int x, int y)
{
	t_surf	*surface1;
	t_surf	*surface2;
	t_v		dest;

	surface1 = NULL;
	surface2 = NULL;
	if (x < env->constants.half_render_w)
	{
		x++;
		dest = (t_v){x * 1.0 / RT__W, y * -1.0 / RT__H, 1.0};
		dest = vecnorm(vec_rotate(env->cam.rotation, dest));
		init_ray(env, dest);
		surface1 = trace_object(env);
	}
	if (y < env->constants.half_render_h)
	{
		y++;
		dest = (t_v){x * 1.0 / RT__W, y * -1.0 / RT__H, 1.0};
		dest = vecnorm(vec_rotate(env->cam.rotation, dest));
		init_ray(env, dest);
		surface2 = trace_object(env);
	}
	if (surf != surface1 || surf != surface2)
		env->sdl.image[RT__W * (y + env->constants.half_render_h) +
			(x + env->constants.half_render_w)] = 0;
}

void			cartoon_effect(t_env *env)
{
	t_v		dest;
	t_surf	*surf;
	int		x;
	int		y;

	y = env->constants.half_render_h * -1;
	while (y < env->constants.half_render_h)
	{
		x = env->constants.half_render_w * -1;
		while (x < env->constants.half_render_w)
		{
			dest = (t_v){x * 1.0 / RT__W, y * -1.0 / RT__H, 1.0};
			dest = vecnorm(vec_rotate(env->cam.rotation, dest));
			init_ray(env, dest);
			surf = trace_object(env);
			check_surf(surf, env, x, y);
			x++;
		}
		y++;
	}
}
