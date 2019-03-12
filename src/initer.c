/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:34:01 by sb_fox            #+#    #+#             */
/*   Updated: 2019/03/12 11:23:11 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_ray(t_env *env, t_v dest)
{
	env->ray.start = env->cam.position;
	env->ray.dest = dest;
	env->ray.min = 1;
	env->ray.max = RAY_LENMAX;
}

void	init_env(t_env *env)
{
	env->imgarr = (t_im **)malloc(sizeof(t_im *) * GUI_BT_NUM * 2);
	env->buttons = (t_bt **)malloc(sizeof(t_bt *) * GUI_BT_NUM);
	env->gui = (t_gui *)malloc(sizeof(t_gui));
	env->hitobj = (t_ho *)malloc(sizeof(t_ho));
	env->hitobj->ishit = -1;
	env->hitobj->index = -1;
	env->cam.rotation = (t_v) {0, 0, 0};
	env->cam.position = (t_v) {0, 0, 0};
	env->mouse_pressed = 0;
}

void	init_mlx(t_env *env)
{
	env->mlx.mlx_ptr = mlx_init();
	env->mlx.win_ptr = mlx_new_window(env->mlx.mlx_ptr,
						WIN_W + GUI_TOOLBAR_W, WIN_H, "Raytracer");
	env->mlx.img_ptr = mlx_new_image(env->mlx.mlx_ptr, WIN_W, WIN_H);
	env->mlx.image = (int *)mlx_get_data_addr(env->mlx.img_ptr,
		&env->mlx.bits, &env->mlx.colms, &env->mlx.endian);
}
