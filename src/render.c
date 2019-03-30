/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 22:20:00 by emayert           #+#    #+#             */
/*   Updated: 2019/03/30 21:29:23 by fdibbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	choose_type(t_env *env, t_lst *surface , double *roots)
{
	if (surface->type == T_PLANE)
		return (intersect_plane(env->ray.start, env->ray.dest,
			surface->obj, roots));
	else if (surface->type == T_SPHERE)
		return (intersect_sphere(env->ray.start, env->ray.dest,
			surface->obj, roots));
	else if (surface->type == T_CYLINDER)
		return (intersect_cylinder(env->ray.start, env->ray.dest,
			surface->obj, roots));
	else if (surface->type == T_CONE)
		return (intersect_cone(env->ray.start, env->ray.dest,
			surface->obj, roots));
	return (0);
}

/* split inner while cycle into another fucntion for norm */

double		closest_intersection(t_env *env, t_lst **closest_surf)
{
	double	closest_dist;
	double	roots[2];
	int		intersect;
	t_lst	*objects;
	t_lst	*surface;

	intersect = 0;
	objects = env->objects;
	closest_dist = env->ray.max;
	while (objects)
	{
		surface = ((t_obj *)objects->obj)->surfaces;
		while (surface)
		{
			intersect = choose_type(env, surface, roots);
			if (intersect && roots[0] > env->ray.min && roots[0] < closest_dist)
			{
				closest_dist = roots[0];
				closest_surf == NULL ? 0 : (*closest_surf = surface);
			}
			if (intersect && roots[1] > env->ray.min && roots[1] < closest_dist)
			{
				closest_dist = roots[1];
				closest_surf == NULL ? 0 : (*closest_surf = surface);
			}
			surface = surface->next;
		}
		objects = objects->next;
	}
	return (closest_dist);
}

t_clr		trace_ray(t_env *env, int recursion)
{
	double	closest_dist;
	t_lst	*closest_surf;
	t_clr	color;

	closest_surf = NULL;
	closest_dist = closest_intersection(env, &closest_surf);
	if (closest_dist >= env->ray.max)
		return ((t_clr){0, 0, 0});
	color = light_on(env, closest_dist, closest_surf, recursion);
	return (color);
}

/*	Casts rays in every viewport pixel and calculated the appropriate color
**	for the pixel, saves into image array and sets it into renderer. */

void		render(t_env *env)
{
	t_v		dest;
	t_clr	color;
	int		x;
	int		y;

	if (env->stereoscopy == 0)
	{
		y = WIN_H / 2 * -1;
		while (y < WIN_H / 2)
		{
			x = WIN_W / 2 * -1;
			while (x < WIN_W / 2)
			{
				dest = (t_v){x * 1.0 / WIN_W, y * -1.0 / WIN_H, 1.0};
				dest = vecnorm(vec_rotate(env->cam.rotation, dest));
				init_ray(env, dest);
				color = trace_ray(env, RECURSION);
				env->sdl.image[WIN_W * (y + WIN_H / 2) + (x + WIN_W / 2)] =
					(color.r << 16) + (color.b << 8) + (color.g);
				sdl_draw(env, color, x, y);
				x++;
			}
			y++;
		}
	}
	else
		stereoscopy(env);
	// blur(env);
	// sepia(env);
	//anti_aliasing(env);
	SDL_RenderPresent(env->sdl.renderer);
}
