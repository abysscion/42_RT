/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:23:36 by cschuste          #+#    #+#             */
/*   Updated: 2019/04/03 10:09:31 by sb_fox           ###   ########.fr       */
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
# include "../lib/libvec/libvec.h"
# include "../lib/libkiss/kiss_sdl.h"
# include "structs.h"
# include "keys.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

/*=================================== GUI ===================================*/
# define	GUI_BAR_H			68
# define	GUI_LBLOCK_W		134
# define	GUI_RBLOCK_W		134

void				init_gui(t_env *e);
void				draw_gui(t_env *e);

/*================================ END OF GUI ===============================*/

/*================================ MAIN =====================================*/
# define MSG_USAGE	"usage: \e[33mThere's no usage yet :^)\e[0m"
# define RAY_LENMAX				2147483647
# define RAY_LENMIN				0.001
# define ROT_STEP				15
# define RT__W					500
# define RT__H					500
# define WIN_H					(RT__H + GUI_BAR_H)
# define WIN_W					(RT__W + GUI_LBLOCK_W + GUI_RBLOCK_W)
# define CLR_BACKGROUND			0

# define T_OBJECT				-1
# define T_PLANE				1
# define T_SPHERE				2
# define T_CYLINDER				3
# define T_CONE					4

# define T_AMBIENT				1
# define T_POINT				2
# define T_DIRECTIONAL			3

# define RECURSION				3

t_clr				light_on(t_env *env, double closest, t_lst *surface, int rec);
t_clr   			calc_refract(t_env *env, t_lc lc, t_lst *surface, int rec);
t_clr				trace_ray(t_env *env, int rec);
t_lst				*lst_to_last(t_lst *lst);
t_lst				*list_add(t_lst *lst);
t_lst				*list_create();
t_v					calc_reflected_ray(t_v bisect, t_v direction);
t_v					vec_rotate(t_v a, t_v vec);
t_v					reflect_ray(t_v n, t_v l);
double				closest_intersection(t_env *env, t_lst **closest_surf);
double				ft_atod(char *str);
void				calc_surf_normal(t_env *env, double closest, t_lst *surface,
															t_lc *light);
void				calc_ref_color(t_clr *color, t_clr *ref_color,
															t_surf *surface);
void    			count_rgb(unsigned char *rgb, unsigned char *ref_col,
															t_env *e, int i);
void				create_any_ob(t_env *e, unsigned char *arr, t_v pos,
															int spec);
void				calc_color(t_clr *color, double intens, t_surf *surface);
void				sdl_draw(t_env *env, t_clr color, int x, int y);
void				get_texture_color(t_surf *surface, t_lc *light);
void				sdl_key_press_events(int key, t_env *env);
void				create_objects(t_env *e, char *av);
void				sdl_help(t_env *env, int x, int y);
void				print_info_about_hitobj(t_env *e);
void				validate_cylinder(char **params);
void				save_image(int *mass, int iter);
void				init_env(t_env *e, char **argv);
void				validate_sphere(char **params);
void				init_ray(t_env *env, t_v dest);
void				rayhit_obj(t_v dest, t_env *e);
void				validate_plane(char **params);
void				validate_cone(char **params);
void				adjust_objects(t_env *env);
void				anti_aliasing(t_env *env);
void				calc_basis(t_surf *surf);
void				init_object(t_obj *obj);
void				stereoscopy(t_env *env);
void				draw_rt(t_env *env);
void				render(t_env *e);
void				sepia(t_env *env);
void				blur(t_env *env);
int					limit_cone_cyl(t_surf *surf,
										t_v dest, t_v start, double *roots);
int					intersect_cylinder(t_v start,
										t_v dest, t_surf *cyl, double *t);
int					intersect_sphere(t_v start,
										t_v dest, t_surf *sph, double *t);
int					intersect_cone(t_v start,
										t_v dest, t_surf *cone, double *t);
int					intersect_plane(t_v start,
										t_v dest, t_surf *plane, double *t);
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
/*=============================== END OF MAIN ===============================*/

/*================================= PARSER ==================================*/
void				parse_file(char *name, t_env *env);
void				parser_validation(char *name);

void				add_surface(int fd, t_obj *obj);
void				write_field(int fd, char ***split,
						char **line, t_surf *surf);

void				parse_next(int fd, char ***split, char **line);
int					check_floats(char **param, int i);
int					check_param_num(char **param, int i);
void				free_words(char **words);
void				invalid_syntax(int object);

int					open_check(int fd, char ***split, char **line);
int					close_check(char ***split, char **line);
int					intensity_check(int fd, char ***split, char **line);
int					texture_check(int fd, char ***split, char **line);
int					color_check(int fd, char ***split, char **line);
int					light_type_check(int fd, char ***split, char **line);
int					surface_type_check(int fd, char ***split, char **line);

int					check_surface(int fd, char ***split, char **line,
						int *object);
void				validate_surface(int fd, int object);

int					check_single_float_field(int fd,
						char ***split, char **line);
int					check_triple_float_field(int fd,
						char ***split, char **line);
/*============================== END OF PARSER ==============================*/

#endif
