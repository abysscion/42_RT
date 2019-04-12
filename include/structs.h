/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:23:36 by sb_fox            #+#    #+#             */
/*   Updated: 2019/04/12 16:57:10 by cschuste         ###   ########.fr       */
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

typedef	struct		s_norme_abuse
{
	int					hrw;
	int					hrh;
}					t_na;

typedef	struct		s_gui
{
	SDL_Event			ev;
	SDL_Renderer		*ren;
	kiss_label			lab_tbx_obj;
	kiss_label			lab_tbx_info;
	kiss_label			lab_eff;
	kiss_entry			ent_pos_x;
	kiss_entry			ent_pos_y;
	kiss_entry			ent_pos_z;
	kiss_entry			ent_rot_x;
	kiss_entry			ent_rot_y;
	kiss_entry			ent_rot_z;
	kiss_array			objarr;
	kiss_array			tbx_obj_arr;
	kiss_array			tbx_info_arr;
	kiss_array			tbx_eff_arr;
	kiss_window			rblock;
	kiss_window			lblock;
	kiss_window			bar;
	kiss_window			background;
	kiss_window			win_info;
	kiss_button			bt_arrup;
	kiss_textbox		tbx_obj;
	kiss_textbox		tbx_info;
	kiss_textbox		tbx_eff;
	kiss_selectbutton	sbt_eff_arr[5];
	int					eff_num;
}					t_gui;

typedef	struct		s_blur
{
	unsigned char		*vec;
    int					*img;
	int					*preprocess;
	int					bheight;
	int					bwidth;
}					t_blur;

typedef	struct		s_lc
{
	t_v					to_start;
	t_v					surf_normal;
	t_v					surf_point;
	t_v					point_to_light;
	t_v					reflect_dir;
	t_v					orig_dest;
	t_v					orig_norm;
}					t_lc;

typedef	struct		s_ray
{
	t_v					start;
	t_v					dest;
	double				min;
	double				max;
}					t_ray;

typedef	struct		s_cam
{
	t_v					rotation;
	t_v					position;
}					t_cam;

typedef	struct		s_clr
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}					t_clr;

typedef	struct		s_basis
{
	t_v					x;
	t_v					y;
	t_v					z;
}					t_basis;

typedef	struct		s_surface
{
	SDL_Surface			*texture;
	t_basis				basis;
	t_clr				color;
	t_v					position_init;
	t_v					orientation_init;
	t_v					position;
	t_v					orientation;
	double				radius;
	double				max_height;
	double				min_height;
	double				specular;
	double				reflect;
	double				transp;
	int					type;
}					t_surf;

typedef	struct		s_ls
{
	struct s_ls			*next;
	void				*obj;
	int					type;
	int					id;
}					t_lst;

/*
**							environment
**								 |
**							  objects
**							/         \
**						 obj           obj->next
**					    /   \         |         \
**					   /     |        |          \
**	      surfaces ————      |         \           ——— surfaces->next
**	         |        surfaces->next    surfaces              |
**	        obj              |             |                 obj
**           |              obj           obj                 |
**      [obj->data]          |             |             [obj->data]
**                      [obj->data]   [obj->data]
*/
typedef	struct		s_object
{
	t_lst				*surfaces;
	t_v					offset;
	t_v					rotation;
}					t_obj;

typedef	struct		s_light
{
	t_v					position;
	double				intensity;
}					t_light;

typedef	struct		s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	int					*image;
}					t_sdl;

typedef	struct		s_flags
{
	int					stereo;
	int					sepia;
	int					blur;
	int					aa;
	int					need_render;
}					t_flg;

typedef	struct		s_environment
{
	t_lst				*lights;
	t_lst				*objects;
	t_cam				cam;
	t_sdl				sdl;
	t_flg				flags;
	t_ray				ray;
	t_gui				*gui;
	t_na				abuse;
	int					quarter;
	
}					t_env;

#endif
