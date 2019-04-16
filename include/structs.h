/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:23:36 by sb_fox            #+#    #+#             */
/*   Updated: 2019/04/16 19:29:03 by sb_fox           ###   ########.fr       */
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

typedef	struct		s_constants
{
	int					half_render_w;
	int					half_render_h;
}					t_const;

typedef	struct		s_gui
{
	kiss_selectbutton	sbt_eff_arr[5];
	kiss_combobox		cbb_light;
	kiss_textbox		tbx_info;
	kiss_textbox		tbx_obj;
	kiss_textbox		tbx_eff;
	kiss_window			background;
	kiss_window			win_info;
	kiss_window			rblock;
	kiss_window			lblock;
	kiss_label			lab_cbb_light;
	kiss_label			lab_info_type;
	kiss_label			lab_info_pos;
	kiss_label			lab_info_rot;
	kiss_label			lab_tbx_info;
	kiss_label			lab_tbx_obj;
	kiss_label			lab_eff;
	kiss_array			cbb_light_arr;
	kiss_array			tbx_info_arr;
	kiss_array			tbx_obj_arr;
	kiss_array			tbx_eff_arr;
	kiss_entry			ent_pos_x;
	kiss_entry			ent_pos_y;
	kiss_entry			ent_pos_z;
	kiss_entry			ent_rot_x;
	kiss_entry			ent_rot_y;
	kiss_entry			ent_rot_z;
	kiss_entry			ent_type;
	kiss_array			objarr;
	SDL_Renderer		*ren;
	SDL_Event			ev;
	void				*selected_object;
	int					selected_object_type;
	int					eff_num;
	int					need_redraw;
	int					need_update_info;
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

typedef struct		s_limits
{
	double			max_height;
	double			min_height;
	double			max_width;
	double			min_width;
}					t_lim;

typedef	struct		s_surface
{
	SDL_Surface			*texture;
	t_basis				basis;
	t_lim				limits;
	t_clr				color;
	t_v					position_init;
	t_v					orientation_init;
	t_v					position;
	t_v					orientation;
	double				radius;
	double				specular;
	double				reflect;
	double				transp;
	int					disruption;
	int					type;

}					t_surf;

typedef	struct		s_ls
{
	struct s_ls			*next;
	void				*obj;
	int					type;
	int					id;
}					t_lst;

typedef	struct		s_object
{
	t_lst				*surfaces;
	t_v					position;
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
	t_const				constants;
	t_lst				*lights;
	t_lst				*objects;
	t_cam				cam;
	t_sdl				sdl;
	t_flg				flags;
	t_ray				ray;
	t_gui				*gui;
	int					quarter;

}					t_env;

#endif
