/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:16:20 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/14 20:38:37 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** need another way to handle u and v being NaN
** other than x < 0 || y < 0 -> return
*/

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

void		get_texture_color(t_surf *surface, t_lc *light)
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
		return ;
	surface->color.r = ((unsigned char *)surface->texture->pixels)[y + x];
	surface->color.g = ((unsigned char *)surface->texture->pixels)[y + x + 1];
	surface->color.b = ((unsigned char *)surface->texture->pixels)[y + x + 2];
}
