/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:16:20 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/21 20:43:24 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


static void	calc_local_coords(t_v *surf_point, t_basis *basis, double *u, double *v)
{
	*u = basis->x.x * surf_point->x + basis->x.y * surf_point->y +
				basis->x.z * surf_point->z;
	*v = basis->y.x * surf_point->x + basis->y.y * surf_point->y +
				basis->y.z * surf_point->z;
}

void		get_texture_color(t_env *env, t_surf *surface, t_lc *light)
{
	int		x;
	int		y;
	double	u;
	double	v;
	double	buff;

	if (surface->basis.x.x == 0 && surface->basis.x.y == 0 &&
		surface->basis.x.z == 0)
		{
			u = light->surf_point.x;
			v = light->surf_point.y;
		}
	else
		calc_local_coords(&light->surf_point, &surface->basis, &u, &v);
	if ((u = modf(u, &buff)) < 0)
		u = 1 + u;
	if ((v = modf(v, &buff)) < 0)
		v = 1 + v;
	x = (int)(u * env->surface->w) * env->surface->format->BytesPerPixel;
	y = (int)(v * env->surface->h) * env->surface->pitch;
	surface->color.r = env->texture[y + x];
	surface->color.g = env->texture[y + x + 1];
	surface->color.b = env->texture[y + x + 2];
}

void 	   load_texture(t_env *env)
{
	//SDL_Surface *normal;
	/*t_clr      color;
	int			i;
	int			x;
	int			y; */

	env->surface = IMG_Load("minecraft.jpg");
	//normal = IMG_Load("rock_normal.jpg");
	env->texture = (unsigned char *)env->surface->pixels;

	/*printf("%d %d %d %d %d\n", texture->w, texture->h, texture->pitch, texture->format->format, texture->format->BitsPerPixel);
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
	SDL_RenderPresent(env->sdl.renderer); */
}