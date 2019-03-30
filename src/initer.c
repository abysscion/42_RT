/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:34:01 by sb_fox            #+#    #+#             */
/*   Updated: 2019/03/30 19:37:29 by fdibbert         ###   ########.fr       */
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
	env->stereoscopy = 0;
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
			surf->orientation = surf->orientation_init;
			surf->position = vecsum(surf->position_init, obj->offset);
			if (surf->type == T_CONE)
				surf->position = vecsub(surf->position,
					vecmult_num(surf->orientation, surf->min_height));
			calc_basis(surf);
			surfs = surfs->next;
		}
		objs = objs->next;
	}
}