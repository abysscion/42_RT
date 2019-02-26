/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <emayert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 20:26:12 by cschuste          #+#    #+#             */
/*   Updated: 2019/02/22 18:17:41 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static	void	create_light(t_env *e)
{
	e->lnum = 1;
	e->light = (t_light **)malloc(sizeof(t_light *) * e->lnum);
	e->light[0] = (t_light *)malloc(sizeof(t_light));
	e->light[0]->type = "point";
	e->light[0]->intensity = 1;
	e->light[0]->pos = (t_v){6, 0, -1};
}

void			create_scene_0(t_env *e)
{
	int		i;

	i = -1;
	e->objs->n_obj = 1;
	e->objs->objarr = (t_obj **)malloc(sizeof(t_obj *) * e->objs->n_obj);
	while (++i < e->objs->n_obj)
		e->objs->objarr[i] = (t_obj *)malloc(sizeof(t_obj));
	i = -1;
	cr_obj((t_bs){0, 0, 6, 0, 0, 0, 1, 100, 0, 0, 10, T_SPHERE}, ++i, e);
	create_light(e);
}
