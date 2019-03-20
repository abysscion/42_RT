/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:23:36 by sb_fox            #+#    #+#             */
/*   Updated: 2019/03/20 17:17:20 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
#  include "SDL.h"
#  include "SDL_image.h"
# else
#  include <CL/cl.h>
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>
# endif
# include "libvec.h"

typedef struct		s_lc
{
	t_v				to_dest;
	t_v				surf_normal;
	t_v				surf_point;
	t_v				point_to_light;
	t_v				reflect_dir;
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

typedef struct	s_surface
{
	t_clr		color;
	t_v			position;
	t_v			orientation;
	double		radius;
	double		specular;
	double		reflect;
	double		transp;
}				t_surf;

typedef	struct	s_light
{
	t_v			position;
	double		intensity;
}				t_light;

typedef struct	s_ls
{
	struct s_ls	*next;
	void		*obj;
	int			type;
	int			id;
}				t_lst;

typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				*image;
}				t_sdl;

typedef	struct	s_environment
{
	t_lst		*lights;
	t_lst		*surfaces;
	t_cam		cam;
	t_sdl		sdl;
	t_ray		ray;
	int			mouse_pressed;
}				t_env;

#endif
