/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:23:36 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/18 18:01:57 by eloren-l         ###   ########.fr       */
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
# include "SDL.h"
# include "SDL_image.h"

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
# define T_AMBIENT				0
# define T_POINT				1
# define T_DIRECTIONAL			2
# define RECURSION				2

t_clr				trace_ray(t_env *env, int rec);
t_clr				light_on(t_env *env, double closest, t_lst *surface, int rec);
void				calc_surf_normal(t_env *env, double closest,
							t_lst *surface, t_lc *light);
t_v					vec_rotate(t_v a, t_v vec);
t_v					reflect_ray(t_v n, t_v l);
t_v					calc_reflected_ray(t_v bisect, t_v direction);
void				render(t_env *e);
double				closest_intersection(t_env *env, t_lst **closest_surf);


void				calc_ref_color(t_clr *color, t_clr *ref_color, t_surf *surface);
void    			count_rgb(unsigned char *rgb, unsigned char *ref_col, t_env *e, int i);
void				calc_color(t_clr *color, double intens, t_surf *surface);
void				translate_obj(double *val, double add, int rd, t_env *e);
void				create_objects(t_env *e, char *av);
void				print_info_about_hitobj(t_env *e);
void				rayhit_obj(t_v dest, t_env *e);
void				create_any_ob(t_env *e,
									unsigned char *arr, t_v pos, int spec);

void				init_mlx(t_env *e);
void				init_env(t_env *e);
void				init_ray(t_env *env, t_v dest);

int					trace_ray_cylinder(t_v dest, t_env *e);
int					trace_ray_sphere(t_v dest, t_env *e);
int					trace_ray_plane(t_v dest, t_env *e);
int					trace_ray_cone(t_v dest, t_env *e);


void				sdl_key_press_events(int key, t_env *env);
int					key_hook(int key, t_env *e);

int					mouse_release(int key, int x, int y, t_env *e);
int					mouse_press(int key, int x, int y, t_env *e);
int					mouse_move(int x, int y, t_env *e);

int					clean_n_close(t_env *e);
int					expose_hook(t_env *e);

int					intersect_cylinder(t_v start,
										t_v dest, t_surf *cyl, double *t);
int					intersect_sphere(t_v start,
										t_v dest, t_surf *sph, double *t);
int					intersect_cone(t_v start,
										t_v dest, t_surf *cone, double *t);
int					intersect_plane(t_v start,
										t_v dest, t_surf *plane, double *t);				

t_lst				*lst_to_last(t_lst *lst);
t_lst				*list_create();
t_lst				*list_add(t_lst *lst);

void				parse_file(char *name, t_env *env);
void				parser_validation(char *name);

void				check_floats(char **param, int i, char *name);
void				check_param_num(char **param, int i, char *name);
void				free_words(char **words);
void				set_surf_type(char *surf, t_lst *lst);

void				validate_sphere(char **params);
void				validate_cylinder(char **params);
void				validate_cone(char **params);
void				validate_plane(char **params);

double				ft_atod(char *str);

void				anti_aliasing(t_env *env);
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
