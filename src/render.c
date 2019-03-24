/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 22:20:00 by emayert           #+#    #+#             */
/*   Updated: 2019/03/24 19:08:53 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		choose_type(t_env *env, t_lst *surface , double *roots)
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

double	closest_intersection(t_env *env, t_lst **closest_surf)
{
	double	closest_dist;
	double	roots[2];
	int		intersect;
	t_lst	*surface;

	intersect = 0;
	surface = env->surfaces;
	closest_dist = env->ray.max;
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
	return (closest_dist);
}

t_clr	trace_ray(t_env *env, int recursion)
{
	double	closest_dist;
	t_lst	*closest_surf;
	t_clr	color;

	closest_surf = 0x0;
	closest_dist = closest_intersection(env, &closest_surf);
	if (closest_dist >= env->ray.max)
		return ((t_clr){0, 0, 0});
	color = light_on(env, closest_dist, closest_surf, recursion);
	return (color);
}

/*
**	Casts rays in every viewport pixel and lighting appropriate pixels
**	on viewport image.
*/

void	render(t_env *env)
{
	t_v		dest;
	t_clr	color;
	int		x;
	int		y;

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
			SDL_SetRenderDrawColor(env->sdl.renderer, color.r, color.g, color.b, 0);
			SDL_RenderDrawPoint(env->sdl.renderer, x + WIN_W / 2, y + WIN_H / 2);
			x++;
		}
		y++;
	}
	//anti_aliasing(env);
	SDL_RenderPresent(env->sdl.renderer);
}
