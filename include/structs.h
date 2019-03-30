/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:23:36 by sb_fox            #+#    #+#             */
/*   Updated: 2019/03/30 18:04:41 by fdibbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
#  include <SDL.h>
#  include <SDL_image.h>
# else
#  include <CL/cl.h>
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>
# endif
# include "libvec.h"

typedef    struct        s_blur
{
	unsigned char	*vec;
    int				*img;
	int				*preprocess;
	int				bheight;
	int				bwidth;
}                    t_blur;

typedef struct		s_lc
{
	t_v				to_start;
	t_v				surf_normal;
	t_v				surf_point;
	t_v				point_to_light;
	t_v				reflect_dir;
	t_v				orig_dest;
	t_v				orig_norm;
}					t_lc;

typedef struct		s_ray
{
	t_v				start;
	t_v				dest;
	double			min;
	double			max;
}					t_ray;

typedef	struct		s_cam
{
	t_v				rotation;
	t_v				position;
}					t_cam;

typedef struct		s_clr
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_clr;

typedef struct		s_basis
{
	t_v				x;
	t_v				y;
	t_v				z;
}					t_basis;

typedef struct		s_surface
{
	SDL_Surface		*texture;
	t_basis			basis;
	t_clr			color;
	t_v				position_init;
	t_v				orientation_init;
	t_v				position;
	t_v				orientation;
	double			radius;
	double			max_height;
	double			min_height;
	double			specular;
	double			reflect;
	double			transp;
	int				type;
}					t_surf;

typedef struct		s_ls
{
	struct s_ls		*next;
	void			*obj;
	int				type;
	int				id;
}					t_lst;

typedef struct		s_object
{
	t_lst			*surfaces;
	t_v				offset;
	t_v				rotation;
}					t_obj;

typedef	struct		s_light
{
	t_v				position;
	double			intensity;
}					t_light;

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				*image;
}					t_sdl;

typedef	struct		s_environment
{
	t_lst			*lights;
	t_lst			*objects;
	t_cam			cam;
	t_sdl			sdl;
	t_ray			ray;
	char			stereoscopy;
}					t_env;

#endif
