/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:34:01 by sb_fox            #+#    #+#             */
/*   Updated: 2019/04/03 15:35:18 by eloren-l         ###   ########.fr       */
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
	env->cam.rotation = (t_v) {0, 0, 0};
	env->cam.position = (t_v) {0, 0, 0};
	env->flags.stereo = 0;
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
			surf->orientation = vec_rotate(obj->rotation,
				surf->orientation_init);
			surf->position = vec_rotate(obj->rotation, surf->position_init);
			surf->position = vecsum(surf->position, obj->offset);
			if (surf->type == T_CONE)
				surf->position = vecsub(surf->position,
					vecmult_num(surf->orientation, surf->min_height));
			calc_basis(surf);
			surfs = surfs->next;
		}
		objs = objs->next;
	}
}