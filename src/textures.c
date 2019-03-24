/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:16:20 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/24 17:46:45 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** no need for angle check if cylinder is not infinite
** and there is not need to take decimal part, just scale
** it to cylinder height - v = v / cyl_height
*/

static void	calc_cylinder_local_coords(t_v *surf_point, t_surf *surface, double *u, double *v)
{
	t_v		center_to_point;
	t_v		sr_pt_base;
	double	cen_to_p_len;
	double	angle;

	center_to_point = vecsub(*surf_point, surface->position);
	cen_to_p_len = veclen(center_to_point);
	angle = vecmult_scal(vecnorm(center_to_point), surface->basis.y);
	*v = angle * cen_to_p_len;
	sr_pt_base = vecsub(*surf_point, vecmult_num(surface->basis.y, *v));
	/*if (angle > 0)
	{
		*v = angle * cen_to_p_len;
		sr_pt_base = vecsub(*surf_point, vecmult_num(surface->basis.y, *v));
	}
	else
	{
		*v = -angle * cen_to_p_len;
		sr_pt_base = vecsub(*surf_point, vecmult_num(surface->basis.y, -(*v)));
	}*/
	center_to_point = vecnorm(vecsub(sr_pt_base, surface->position));
	angle = vecmult_scal(center_to_point, surface->basis.x);
	if (vecmult_scal(vecmult_vec(surface->basis.x, surface->basis.y), center_to_point) > 0)
	{
		*u = acos(vecmult_scal(center_to_point, surface->basis.x)) / (2 * M_PI);	

	}
	else
	{
		*u = (acos(vecmult_scal(center_to_point, surface->basis.x)) + M_PI) / (2 * M_PI);
		*u = fabs(*u - 1) + 0.5;
	}
}

static void get_cylinder_texture_color(t_surf *surface, t_lc *light)
{
	int		x;
	int		y;
	double	u;
	double	v;

	calc_cylinder_local_coords(&light->surf_point, surface, &u, &v);
	x = (int)(u * surface->texture->w) *
		surface->texture->format->BytesPerPixel;
	y = (int)(v * surface->texture->h) *
		surface->texture->pitch;
	if (x < 0 || y < 0)
		return ;
	surface->color.r = ((unsigned char *)surface->texture->pixels)[y + x];
	surface->color.g = ((unsigned char *)surface->texture->pixels)[y + x + 1];
	surface->color.b = ((unsigned char *)surface->texture->pixels)[y + x + 2];
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

static void get_sphere_texture_color(t_surf *surface, t_lc *light)
{
	int		x;
	int		y;
	double	u;
	double	v;

	calc_sphere_local_coords(&light->surf_point, surface, &u, &v);
	x = (int)(u * surface->texture->w) *
		surface->texture->format->BytesPerPixel;
	y = (int)(v * surface->texture->h) *
		surface->texture->pitch;
	if (x < 0 || y < 0)
		return ;
	surface->color.r = ((unsigned char *)surface->texture->pixels)[y + x];
	surface->color.g = ((unsigned char *)surface->texture->pixels)[y + x + 1];
	surface->color.b = ((unsigned char *)surface->texture->pixels)[y + x + 2];
}

static void	calc_local_coords(t_v *surf_point, t_basis *basis, double *u, double *v)
{
	*u = basis->x.x * surf_point->x + basis->x.y * surf_point->y +
				basis->x.z * surf_point->z;
	*v = basis->y.x * surf_point->x + basis->y.y * surf_point->y +
				basis->y.z * surf_point->z;
}

void		get_texture_color(t_surf *surface, t_lc *light)
{
	int		x;
	int		y;
	double	u;
	double	v;
	double	buff;

	if (surface->type == T_SPHERE)
	{
		get_sphere_texture_color(surface, light);
		return ;
	}
	if (surface->type == T_CYLINDER)
	{	
		get_cylinder_texture_color(surface, light);
		return ;
	}
	calc_local_coords(&light->surf_point, &surface->basis, &u, &v);
	if ((u = modf(u, &buff)) < 0)
		u = 1 + u;
	if ((v = modf(v, &buff)) < 0)
		v = 1 + v;
	x = (int)(u * surface->texture->w) *
		surface->texture->format->BytesPerPixel;
	y = (int)(v * surface->texture->h) *
		surface->texture->pitch;
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