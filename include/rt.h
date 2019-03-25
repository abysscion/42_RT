/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:23:36 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/25 17:02:28 by eloren-l         ###   ########.fr       */
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
# include "structs.h"
# include "keys.h"
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <math.h>

/*================================ MAIN =====================================*/
# define MSG_USAGE	"usage: \e[33mThere's no usage yet :^)\e[0m"
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
# define RECURSION				3

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
t_clr   			calc_refract(t_env *env, t_lc lc, t_lst *surface, int rec);
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

void				get_texture_color(t_surf *surface, t_lc *light);
void				calc_basis(t_surf *surf);

int					limit_cone_cyl(t_surf *surf, t_v dest, t_v start, double *roots);
/*=============================== END OF MAIN ===============================*/

/*=================================== GUI ===================================*/

/*================================ END OF GUI ===============================*/

#endif
