/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:01:25 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/13 17:39:30 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/* t_v	get_texture_normal(t_surf *surface, t_lc *light)
{
	int		x;
	int		y;
	double	u;
	double	v;

	u = 0;
	v = 0;
	if (surface->type == T_PLANE)
		calc_plane_local_coords(&light->surf_point, surface, &u, &v);
	else if (surface->type == T_SPHERE)
		calc_sphere_local_coords(&light->surf_point, surface, &u, &v);
	else if (surface->type == T_CYLINDER || surface->type == T_CONE ||
			surface->type == T_PARAB)
		calc_cone_cyl_local_coords(&light->surf_point, surface, &u, &v);
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
} */