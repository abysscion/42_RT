/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:23:36 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/02 04:15:11 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
#  define M_PI			3.14159265359
# endif
# include "../lib/libft/libft.h"
# include "../lib/libmlx/mlx.h"
# include "../lib/libvec/libvec.h"
# include "keys.h"
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <math.h>

# define MSG_USAGE	"usage: \e[33mThere's no usage yet :^)\e[0m"
# define KeyPressMask			(1L<<0)
# define KeyReleaseMask			(1L<<1)
# define ButtonPressMask		(1L<<2)
# define ButtonReleaseMask		(1L<<3)
# define EnterWindowMask		(1L<<4)
# define LeaveWindowMask		(1L<<5)
# define PointerMotionMask		(1L<<6)
# define PointerMotionHintMask	(1L<<7)
# define Button1MotionMask		(1L<<8)
# define Button2MotionMask		(1L<<9)
# define RAY_LENMAX				2147483647
# define RAY_LENMIN				0.001
# define ROT_STEP				15
# define WIN_H					512
# define WIN_W					512
# define CLR_BACKGROUND			0
# define T_PLANE				0
# define T_SPHERE				1
# define T_CYLINDER				2
# define T_CONE					3

typedef	struct		s_camera
{
	t_v		rot;
	t_v		pos;
	void	*ptr_vp;
	int		*view_port_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}					t_cam;

typedef	struct		s_light
{
	t_v		pos;
	double	intensity;
	char	*type;
}					t_light;

typedef struct		s_render
{
	t_v		start;
	t_v		dest;
	double	min;
	int		max;
}					t_ren;

typedef	struct		s_object
{
	t_v					pos;
	t_v					rot;
	unsigned	char	colour[3];
	double				radius;
	int					specular;
	int					type;
}					t_obj;

typedef struct		s_light_container
{
	t_v		p;
	t_v		n;
	t_v		v;
	t_v		l;
	t_v		r;
	int		temp;
}					t_lc;

typedef	struct		s_objects_container
{
	t_obj	**objarr;
	int		n_cylinders;
	int		n_planes;
	int		n_sphere;
	int		n_cones;
	int		n_obj;
}					t_oc;

typedef	struct		s_hitobject
{
	int	index;
	int	ishit;
	int	type;
}					t_ho;

typedef	struct		s_bullshit
{
	double				posx;
	double				posy;
	double				posz;
	double				rotx;
	double				roty;
	double				rotz;
	double				rad;
	unsigned	char	r;
	unsigned	char	g;
	unsigned	char	b;
	int					spec;
	int					type;
}					t_bs;

typedef	struct		s_button
{
	t_v		pos;
	int		len;
	int		wid;
	int		state;
	char	*fname;
	void	*imgon;
	void	(*foo)(double *, double, int *);
}					t_bt;

typedef	struct		s_environment
{
	t_light	**light;
	t_cam	*cam;
	t_ren	*ren_var;
	t_bt	**buttons;
	t_lc	*lit_var;
	t_oc	*objs;
	t_ho	*hitobj;
	void	*mlx;
	void	*win;
	int		need_redraw;
	int		mouse_pressed;
	int		lnum;
	int		k;
}					t_env;


t_v					normal2plane(t_env	*e, int i);
t_v					normal2cone(t_env *e, t_v dest, double closest, int i);
t_v					normal2cyl(t_env *e, t_v dest, double closest, int i);
t_v					vec_rotate(t_v a, t_v vec);
t_v					vp_to_global(t_v vp_p);
double				close_intersection(t_env *e, t_ren *r_v, int *num_obj);
void				create_any_ob(t_env *e,
									unsigned char *arr, t_v pos, int spec);
void				light_abuse(int *i, double *intens);
void				ppx_on_img(int x, int y, int color, t_env *e);
void				cr_obj(t_bs bs, int i, t_env *e);
void				create_objects(t_env *e, char *av);
void				rayhit_obj(t_v dest, t_env *e);
void				print_info_about_hitobj(t_env *e);
void				key_handler(int key, t_env *e);
void				create_scene_0(t_env *e);
void				create_scene_1(t_env *e);
void				create_scene_2(t_env *e);
void				create_scene_3(t_env *e);
void				create_scene_4(t_env *e);
void				init_mlx(t_env *e);
void				init_env(t_env *e);
void				render(t_env *e);
int					choose_type(t_env *e, int i, t_ren *r_v, double *t);
int					light_on(t_env *e, t_v dest, double closest, int i);
int					mouse_release(int key, int x, int y, t_env *e);
int					mouse_press(int key, int x, int y, t_env *e);
int					trace_ray_cylinder(t_v dest, t_env *e);
int					trace_ray_sphere(t_v dest, t_env *e);
int					trace_ray_plane(t_v dest, t_env *e);
int					mouse_move(int x, int y, t_env *e);
int					trace_ray_cone(t_v dest, t_env *e);
int					key_hook(int key, t_env *e);
int					clean_n_close(t_env *e);
int					expose_hook(t_env *e);
int					intersect_cylinder(t_v start,
										t_v dest, t_obj *cyl, double *t);
int					intersect_sphere(t_v start,
										t_v dest, t_obj *sph, double *t);
int					intersect_cone(t_v start,
										t_v dest, t_obj *cone, double *t);
int					intersect_plane(t_v start,
										t_v dest, t_obj *plane, double *t);

/*=================================== GUI ===================================*/
# define GUI_ICON_SIZE	64
# define GUI_GAP		5
# define GUI_BT_NUM		4
# define GUI_MARGIN		5

t_bt				*new_bt(int x, int y, char *name, t_env *e);
void				press_mv_button(double *val, double add, int *need_redraw);
void				handle_gui_click(int x, int y, t_env *e);
void				init_buttons(t_env *e);
void				draw_gui(t_env *e);
/*===========================================================================*/

#endif
