/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <emayert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 20:26:12 by cschuste          #+#    #+#             */
/*   Updated: 2019/02/22 19:37:18 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static	void	create_light(t_env *e)
{
	e->lnum = 2;
	e->light = (t_light **)malloc(sizeof(t_light *) * e->lnum);
	e->light[1] = (t_light *)malloc(sizeof(t_light));
	e->light[1]->type = "ambient";
	e->light[1]->intensity = 0.2;
	e->light[0] = (t_light *)malloc(sizeof(t_light));
	e->light[0]->type = "point";
	e->light[0]->intensity = 0.8;
	e->light[0]->pos = (t_v){4, -2, 4};
}

void			create_scene_3(t_env *e)
{
	int		i;

	i = -1;
	e->objs->n_obj = 5;
	e->objs->objarr = (t_obj **)malloc(sizeof(t_obj *) * e->objs->n_obj);
	while (++i < e->objs->n_obj)
		e->objs->objarr[i] = (t_obj *)malloc(sizeof(t_obj));
	i = -1;
	cr_obj((t_bs){-4, 2, 20, 0.75, -1, 0,
	1.75, 0, 200, 0, 0, T_CYLINDER}, ++i, e);
	cr_obj((t_bs){3, 1, 20, -0.6, -1, 0,
	0.7, 180, 180, 0, 50, T_CONE}, ++i, e);
	cr_obj((t_bs){0, 2.2, 19, 0, 0, 0, 2.2, 180, 0, 0, 6, T_SPHERE}, ++i, e);
	cr_obj((t_bs){0, 0, 40, 0, 0, -1, 0, 80, 40, 250, 0, T_PLANE}, ++i, e);
	cr_obj((t_bs){0, 4, 0, 0, -1, 0, 0, 150, 60, 60, 0, T_PLANE}, ++i, e);
	create_light(e);
}
