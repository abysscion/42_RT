/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:34:01 by sb_fox            #+#    #+#             */
/*   Updated: 2019/04/16 19:09:45 by eloren-l         ###   ########.fr       */
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

void	init_env(t_env *env, char **argv)
{
	env->sdl.image = (int *)malloc(sizeof(int) * WIN_H * WIN_W);
	env->gui = (t_gui *)malloc(sizeof(t_gui));
	kiss_array_new(&env->gui->objarr);
	env->sdl.renderer = kiss_init(argv[1], &env->gui->objarr, WIN_W, WIN_H);
	env->abuse.hrw = RT__W / 2;
	env->abuse.hrh = RT__H / 2;
	env->cam.rotation = (t_v) {0, 0, 0};
	env->cam.position = (t_v) {0, 0, 0};
	env->flags.need_render = 1;
}

void	adjust_objects(t_env *env)
{
	t_lst	*objs;
	t_obj	*obj;
	t_lst	*surfs;
	t_surf	*surf;

	objs = env->objects;
	while (objs)
	{
		obj = (t_obj *)objs->obj;
		surfs = obj->surfaces;
		while (surfs)
		{
			surf = (t_surf *)surfs->obj;
			surf->orientation_init = vecnorm(surf->orientation_init);
			surf->orientation = vec_rotate(obj->rotation,
				surf->orientation_init);
			if (surf->type == T_PLANE || surf->type == T_DISC)
				surf->position = vecsum(surf->position_init, obj->offset);
			else
			{
				surf->position = vec_rotate(obj->rotation, surf->position_init);
				surf->position = vecsum(surf->position, obj->offset);
			}
			if (surf->limits.min_height != -INFINITY)
				surf->position = vecsub(surf->position,
					vecmult_num(surf->orientation, surf->limits.min_height));
			calc_basis(surf);
			surfs = surfs->next;
		}
		objs = objs->next;
	}
}
