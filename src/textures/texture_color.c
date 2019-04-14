/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:16:20 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/13 18:34:30 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** need another way to handle u and v being NaN
** other than x < 0 || y < 0 -> return
*/

void	get_texture_color(t_surf *surface, t_lc *light)
{
	int		x;
	int		y;
	double	u;
	double	v;
	double	buff;

	u = 0;
	v = 0;
	if (surface->type == T_PLANE)
	{
		calc_plane_local_coords(&light->surf_point, surface, &u, &v);
		if ((u = modf(u, &buff)) < 0)
			u = 1 + u;
		if ((v = modf(v, &buff)) < 0)
			v = 1 + v;
	}
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

	SDL_CreateWindowAndRenderer(RT__H, RT__W, 0, &window, &render);

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
