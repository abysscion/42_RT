/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:23:36 by sb_fox            #+#    #+#             */
/*   Updated: 2019/03/07 15:07:33 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../lib/libvec/libvec.h"

typedef	struct		s_camera
{
	t_v				rot;
	t_v				pos;
	void			*ptr_vp;
	int				*view_port_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_cam;

typedef	struct		s_light
{
	t_v				pos;
	double			intensity;
	char			*type;
}					t_light;

typedef struct		s_render
{
	t_v				start;
	t_v				dest;
	double			min;
	int				max;
}					t_ren;

typedef	struct		s_object
{
	t_v				pos;
	t_v				rot;
	unsigned char	colour[3];
	double			radius;
	int				specular;
	double			reflect;
	double			transp;
	int				type;
}					t_obj;

typedef struct		s_light_container
{
	t_v				p;
	t_v				n;
	t_v				v;
	t_v				l;
	t_v				r;
	int				temp;
}					t_lc;

typedef	struct		s_objects_container
{
	t_obj			**objarr;
	int				n_cylinders;
	int				n_planes;
	int				n_sphere;
	int				n_cones;
	int				n_obj;
}					t_oc;

typedef	struct		s_hitobject
{
	int				index;
	int				ishit;
	int				type;
}					t_ho;

typedef	struct		s_bullshit
{
	double			posx;
	double			posy;
	double			posz;
	double			rotx;
	double			roty;
	double			rotz;
	double			rad;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				spec;
	double			reflect;
	double			transp;
	int				type;
}					t_bs;

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

typedef	struct		s_environment
{
	t_light			**light;
	t_ren			*ren_var;
	t_cam			*cam;
	t_gui			*gui;
	t_bt			**buttons;
	t_lc			*lit_var;
	t_im			**imgarr;
	t_ho			*hitobj;
	t_oc			*objs;
	void			*mlx;
	void			*win;
	int				mouse_pressed;
	int				need_rerender;
	int				need_regui;
	int				lnum;
	int				k;
}					t_env;

#endif
