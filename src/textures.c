/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:16:20 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/02 16:05:46 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


static void	calc_cone_cyl_local_coords(t_v *surf_p, t_surf *surface, double *u, double *v)
{
	t_v		surf_point;
	t_v		center_to_point;
	t_v		sr_pt_base;
	double	cen_to_p_len;
	double	angle;

	surf_point = vecsub(*surf_p,
		vecmult_num(surface->orientation, surface->min_height));
	center_to_point = vecsub(surf_point, surface->position);
	cen_to_p_len = veclen(center_to_point);
	angle = vecmult_scal(vecnorm(center_to_point), surface->basis.y);
	*v = angle * cen_to_p_len;
	sr_pt_base = vecsub(surf_point, vecmult_num(surface->basis.y, *v));
	center_to_point = vecnorm(vecsub(sr_pt_base, surface->position));
	angle = vecmult_scal(center_to_point, surface->basis.x);
	if (vecmult_scal(vecmult_vec(surface->basis.x, surface->basis.y), center_to_point) > 0)
		*u = acos(vecmult_scal(center_to_point, surface->basis.x)) / (2 * M_PI);	
	else
	{
		*u = (acos(vecmult_scal(center_to_point, surface->basis.x)) + M_PI) / (2 * M_PI);
		*u = fabs(*u - 1) + 0.5;
	}
	*v = *v / (surface->max_height - surface->min_height);
}

static void	calc_sphere_local_coords(t_v *surf_point, t_surf *surface, double *u, double *v)
{
	t_v		center_to_point;
	double	phi;
	double	theta;

	center_to_point = vecnorm(vecsub(*surf_point, surface->position));
	phi = acos(vecmult_scal(surface->basis.y, center_to_point));
	*v = phi / M_PI;
	theta = (acos(vecmult_scal(center_to_point, surface->basis.x) / sin(phi))) / (2 * M_PI);
	if (vecmult_scal(vecmult_vec(surface->basis.x, surface->basis.y), center_to_point) > 0)
		*u = theta;
	else
		*u = 1 - theta;
}

static void	calc_plane_local_coords(t_v *surf_point, t_surf *surface, double *u, double *v)
{
	double	buff;
	t_basis	*basis;

	basis = &surface->basis;
	*u = basis->x.x * surf_point->x + basis->x.y * surf_point->y +
				basis->x.z * surf_point->z;
	*v = basis->y.x * surf_point->x + basis->y.y * surf_point->y +
				basis->y.z * surf_point->z;
	if ((*u = modf(*u, &buff)) < 0)
		*u = 1 + *u;
	if ((*v = modf(*v, &buff)) < 0)
		*v = 1 + *v;
}

/*
** need another way to handle u and v being NaN 
** other than x < 0 || y < 0 -> return
*/

void		get_texture_color(t_surf *surface, t_lc *light)
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
	else if (surface->type == T_CYLINDER || surface->type == T_CONE)
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
}

/*void		texture_tester()
{
	SDL_Window		*window;
	SDL_Renderer	*render;
	SDL_Surface		*texture;
	unsigned char	*pixel;
	t_clr			color;
	int				i;
	int				x;
	int				y;

	texture = IMG_Load("textures/wall.png");
	pixel = (unsigned char *)texture->pixels;

	SDL_CreateWindowAndRenderer(WIN_H, WIN_W, 0, &window, &render);

	printf("%d %d %d %d %d\n", texture->w, texture->h, texture->pitch, texture->format->format, texture->format->BitsPerPixel);
	printf("%d %d %d %d\n", texture->format->Rmask, texture->format->Gmask, texture->format->Bmask, texture->format->Amask);
	while(y < texture->h)
	{
		x = 0;
		i = 0;
		while (x < texture->w)
		{
			color.r = pixel[y * texture->pitch + i++];
			color.g = pixel[y * texture->pitch + i++];
			color.b = pixel[y * texture->pitch + i++];
			SDL_SetRenderDrawColor(env->sdl.renderer, color.r, color.g, color.b, 0);
			SDL_RenderDrawPoint(env->sdl.renderer, x, y);
			x++;
		}
		y++;
	}
	SDL_RenderPresent(env->sdl.renderer);
} */