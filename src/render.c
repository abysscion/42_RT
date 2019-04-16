/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 22:20:00 by emayert           #+#    #+#             */
/*   Updated: 2019/04/16 19:12:11 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				choose_type(t_env *env, t_lst *surface, double *roots)
{
	if (surface->type == T_PLANE || surface->type == T_DISC)
		return (intersect_plane(&(env->ray.start), &(env->ray.dest),
			surface->obj, roots));
	else if (surface->type == T_SPHERE)
		return (intersect_sphere(&(env->ray.start), &(env->ray.dest),
			surface->obj, roots));
	else if (surface->type == T_CYLINDER)
		return (intersect_cylinder(&(env->ray.start), &(env->ray.dest),
			surface->obj, roots));
	else if (surface->type == T_CONE)
		return (intersect_cone(&(env->ray.start), &(env->ray.dest),
			surface->obj, roots));
	else if (surface->type == T_PARAB)
		return (intersect_paraboloid(&(env->ray.start), &(env->ray.dest),
			surface->obj, roots));
	else
		return (0);
}

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

double			closest_intersection(t_env *env, t_surf **closest_surf)
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

t_clr			trace_ray(t_env *env, int recursion)
{
	double	closest_dist;
	t_surf	*closest_surf;
	t_clr	color;

	closest_surf = NULL;
	closest_dist = closest_intersection(env, &closest_surf);
	if (closest_dist >= env->ray.max)
		return ((t_clr){0, 0, 0});
	color = light_on(env, closest_dist, closest_surf, recursion);
	return (color);
}

/*
**	Casts rays in every viewport pixel and calculates appropriate color
**	of the pixel then saves pixel color into sdl.image.
*/

int				render(void *environment)
{
	t_env	*env;
	t_v		dest;
	t_clr	color;
	int		x;
	int		y;

	env = (t_env *)environment;
	y = env->abuse.hrh * -1 + env->quarter;
	while (y < env->abuse.hrh)
	{
		x = env->abuse.hrw * -1;
		while (x < env->abuse.hrw)
		{
			dest = (t_v){x * 1.0 / RT__W, y * -1.0 / RT__H, 1.0};
			dest = vecnorm(vec_rotate(env->cam.rotation, dest));
			init_ray(env, dest);
			color = trace_ray(env, RECURSION);
			env->sdl.image[RT__W *
				(y + env->abuse.hrh) + (x + env->abuse.hrw)] =
				(color.r << 16) + (color.b << 8) + (color.g);
			x++;
		}
		y += THREADS;
	}
	return (0);
}
