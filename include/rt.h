/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:23:36 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/07 15:39:01 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
#  define M_PI					3.14159265359
# endif
# include "../lib/libft/libft.h"
# include "../lib/libmlx/mlx.h"
# include "../lib/libvec/libvec.h"
# include "structs.h"
# include "keys.h"
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <math.h>

/*================================ MAIN =====================================*/
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
# define RECURSION				2

unsigned	char	*light_on(t_env *e, t_ren *r_v, double *closest, int i, int rec);
unsigned	char	*trace_ray(t_ren *ren_var, t_env *e, int rec);
t_v					normal2cone(t_env *e, t_v dest, double closest, int i);
t_v					normal2cyl(t_env *e, t_v dest, double closest, int i);
t_v					normal2plane(t_env	*e, int i);
t_v					vec_rotate(t_v a, t_v vec);
t_v					reflect_ray(t_v n, t_v l);
t_v					vp_to_global(t_v vp_p);
double				*close_intersection(t_env *e, t_ren *r_v, int *num_obj);
double				max_color(double intens, unsigned char col, int *remain);
void    			count_reflect(unsigned char *rgb, unsigned char *ref_col, t_env *e, int i);
void    			count_transp(unsigned char *rgb, unsigned char *ref_col, t_env *e, int i);
void    			limit_specular(unsigned char *rgb, int remain, double intens);
void				translate_obj(double *val, double add, int rd, t_env *e);
void				ppx_on_img(int x, int y, int color, t_env *e);
void				light_abuse(int *i, double *intens);
void				create_objects(t_env *e, char *av);
void				print_info_about_hitobj(t_env *e);
void				create_renvar(t_env *e, t_v dest);
void				cr_obj(t_bs bs, int i, t_env *e);
void				rayhit_obj(t_v dest, t_env *e);
void				key_handler(int key, t_env *e);
void				create_scene_0(t_env *e);
void				create_scene_1(t_env *e);
void				create_scene_2(t_env *e);
void				create_scene_3(t_env *e);
void				create_scene_4(t_env *e);
void				init_mlx(t_env *e);
void				init_env(t_env *e);
void				render(t_env *e);
void				create_any_ob(t_env *e,
									unsigned char *arr, t_v pos, int spec);
int					choose_type(t_env *e, int i, t_ren *r_v, double *t);
int					mouse_release(int key, int x, int y, t_env *e);
int					mouse_press(int key, int x, int y, t_env *e);
int					trace_ray_cylinder(t_v dest, t_env *e);
int					trace_ray_sphere(t_v dest, t_env *e);
int					trace_ray_plane(t_v dest, t_env *e);
int					trace_ray_cone(t_v dest, t_env *e);
int					mouse_move(int x, int y, t_env *e);
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
/*=============================== END OF MAIN ===============================*/

/*=================================== GUI ===================================*/
# define GUI_TEXT_H				20
# define GUI_MSG_NOOBJ_W		(18 * 3)
# define GUI_ICON_SIZE			64
# define GUI_GAP				10
# define GUI_MARGIN				10
# define GUI_TOOLBAR_W			(GUI_GAP * 2 + GUI_ICON_SIZE * 3\
								+ GUI_MARGIN * 2)
# define GUI_BT_NUM				6
# define GUI_BT_CUBE			1
# define GUI_BT_CAM				0
# define GUI_BT_AL				2
# define GUI_BT_AR				3
# define GUI_BT_AU				4
# define GUI_BT_AD				5
# define CLR_TEXT				0x87ceeb
# define T_NAME_LEN_MAX			30
# define T_TYPES_COUNT			4
# define T_PLANE_NAME			"Infinite plane"
# define T_SPHERE_NAME			"Sphere"
# define T_CYLINDER_NAME		"Infinite cylinder"
# define T_CONE_NAME			"Infinite cone"

t_bt				*new_button(int x, int y, int i, t_env *e);
t_bt				*new_bt(int x, int y, int i, t_env *e);
void				press_mv_button(double *val, double add, void *e);
void				draw_object_info(int x, int y, t_env *e);
void				init_buttons(t_env *e);
void				init_icons(t_env *e);
void				init_gui(t_env *e);
void				draw_gui(t_env *e);
int					is_within_border(int x, int y, int bt_index, t_env *e);
int					handle_gui_click(int x, int y, t_env *e);
/*================================ END OF GUI ===============================*/

#endif
