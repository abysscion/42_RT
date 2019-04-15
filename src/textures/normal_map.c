/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:01:25 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/15 21:32:00 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void calc_normal(int x, int y, t_surf *surf)
{
	t_v	buff;

	surf->current_normal.x =
	(((unsigned char *)surf->texture->pixels)[y + x]) * 2 / 255 - 1;
	surf->current_normal.y =
	(((unsigned char *)surf->texture->pixels)[y + x + 1]) * 2 / 255 - 1;
	surf->current_normal.z =
	(((unsigned char *)surf->texture->pixels)[y + x + 2]) / -128 + 1;
	buff.x = surf->basis.x.x * surf->current_normal.x +
			surf->basis.x.y * surf->current_normal.y +
			surf->basis.x.z * surf->current_normal.z;
	buff.y = surf->basis.y.x * surf->current_normal.x +
			surf->basis.y.y * surf->current_normal.y +
			surf->basis.y.z * surf->current_normal.z;
	buff.z = surf->basis.z.x * surf->current_normal.x +
			surf->basis.z.y * surf->current_normal.y +
			surf->basis.z.z * surf->current_normal.z;
	surf->current_normal = vecnorm(buff);
}

static void	get_local_coords(t_surf *surface, t_lc *light, double *u, double *v)
{
	double buff;

	*u = 0;
	*v = 0;
	if (surface->type == T_PLANE || surface->type == T_DISC)
	{
		calc_plane_local_coords(&light->surf_point, surface, u, v);
		if ((*u = modf(*u, &buff)) < 0)
			*u = 1 + *u;
		if ((*v = modf(*v, &buff)) < 0)
			*v = 1 + *v;
	}
	else if (surface->type == T_SPHERE)
		calc_sphere_local_coords(&light->surf_point, surface, u, v);
	else if (surface->type == T_CYLINDER || surface->type == T_CONE ||
			surface->type == T_PARAB)
		calc_conic_local_coords(&light->surf_point, surface, u, v);
}

void		get_texture_normal(t_surf *surface, t_lc *light)
{
	int		x;
	int		y;
	double	u;
	double	v;

	get_local_coords(surface, light, &u, &v);
	x = (int)(u * surface->texture->w) *
		surface->texture->format->BytesPerPixel;
	y = (int)(v * surface->texture->h) *
		surface->texture->pitch;
	if (x < 0 || x > (surface->texture->w *
		surface->texture->format->BytesPerPixel) || y < 0 ||
		y > surface->texture->h * surface->texture->pitch)
	{
		light->surf_normal = surface->current_normal;
		return ;
	}	
	calc_normal(x, y, surface);
	light->surf_normal = surface->current_normal;
}
