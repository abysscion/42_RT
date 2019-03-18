/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:23:36 by sb_fox            #+#    #+#             */
/*   Updated: 2019/03/18 18:02:29 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libvec.h"
# include "SDL.h"
# include "SDL_image.h"

typedef	struct		s_hitobject
{
	int				index;
	int				ishit;
	int				type;
}					t_ho;

typedef	struct		s_image
{
	void			*ptimg;
	char			*path;
	int				len;
	int				wid;
}					t_im;

typedef	struct		s_button
{
	t_v				pos;
	int				len;
	int				wid;
	int				state;
	void			*ptimg;
	void			(*foo)(double *, double, void *);
}					t_bt;

typedef	struct		s_graphical_user_interface
{
	char			**objs_types;
	void			*pt_back_img;
}					t_gui;

//=============================

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

/*typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*image;
	int			bits;
	int			colms;
	int			endian;
}				t_mlx; */

typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				*image;
}				t_sdl;

typedef	struct	s_environment
{
	t_gui		*gui;
	t_ho		*hitobj;
	t_bt		**buttons;
	t_im		**imgarr;

	t_lst		*lights;
	t_lst		*surfaces;
	t_cam		cam;
	t_sdl		sdl;
	t_ray		ray;
	int			mouse_pressed;
	int			need_rerender;
	int			need_regui;
}				t_env;

#endif
